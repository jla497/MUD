#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>
#include <vector>
#include <typeinfo>
#include <boost/format.hpp>
#include <boost/optional.hpp>

#include "connectionmanager/ConnectionManager.h"
#include "controllers/CharacterController.h"
#include "entities/CharacterEntity.h"
#include "gamemanager/GameManager.h"
#include "logging.h"
#include "persistence/PersistenceService.h"
#include "resources/PlayerCharacterDefaults.h"
#include "controllers/AiController.h"

namespace mudserver {
namespace gamemanager {

namespace pc = mudserver::resources::playercharacter;

using boost::format;
using boost::str;

using connection::gameAndUserInterface;

GameManager::GameManager(connection::ConnectionManager &connMan,
                         GameState &gameState,
                         persistence::PersistenceService &persistenceService)
    : gameState{gameState}, connectionManager{connMan},
      persistenceService{persistenceService} {}

/**
 * Runs a standard game loop, which consists of the following steps:
 *      - get user input (messages from the server)
 *      - update the game state using the input
 *      - render, i.e. send broadcast messages to players.
 */
void GameManager::mainLoop() {
    static auto logger = logging::getLogger("GameManager::mainLoop");
    logger->info("Entered main game loop");
    loadPersistedData();

    using clock = std::chrono::high_resolution_clock;

    // point currentActionQueuePtr to actionQueueA
    // point nextActionQueuePtr to actionQueueB
    currentAQueuePtr = &actionsA;
    nextAQueuePtr = &actionsB;

    gameState.doReset();
        //get chars from each room, make ai controller for each npc and insert into controller
        //queue. Note if Player field is a nullptr, this should be taken as a npc controller
        auto npcs = gameState.getAllNpcs();
        assert(!npcs.empty());
        for(auto npc : npcs) {
            auto controller = new AiController();
            controller->init(&gameState, npc, nullptr);

            controllerQueue.push_back(controller);
        }
        logger->debug("done creating npc controllers");
    // queue of characterControllers

    while (!done) {
        auto startTime = clock::now();

        if (connectionManager.update()) {
            // An error was encountered, stop
            done = true;
            continue;
        }

        auto messages = connectionManager.sendToGameManager();
        processMessages(messages);
        fetchCntrlCmds();
        performQueuedActions();
        swapQueuePtrs();
        sendMessagesToPlayers();

        auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(
            clock::now() - startTime);
        std::this_thread::sleep_for(tick - delta);
    }

    persistData();
}

void GameManager::persistData() {
    persistenceService.save(playerService);
    persistenceService.save(gameState);
}

void GameManager::loadPersistedData() {
    playerService = persistenceService.loadPlayerService();
}

Player *GameManager::getPlayerFromLogin(const gameAndUserInterface &message) {
    static auto logger = logging::getLogger("GameManager::getPlayerFromLogin");

    // look up player from ID
    auto connectionId = message.conn.id;
    logger->debug(std::to_string(connectionId) + ": " + message.text);

    auto player = playerService.getPlayerByConnection(connectionId);
    if (!player) {
        auto uAndP = commandParser.identifiersFromIdentifyCommand(message.text);
        if (!uAndP.first.empty()) {
            player = playerService.identify(uAndP.first, uAndP.second);
            if (!player) {
                auto addPlayerResult =
                    playerService.addPlayer(uAndP.first, uAndP.second);
                if (addPlayerResult == AddPlayerResult::playerAdded) {
                    player = playerService.identify(uAndP.first, uAndP.second);
                } else if (addPlayerResult == AddPlayerResult::playerExists) {
                    enqueueMessage(message.conn, INCORRECT_IDENT);
                }
            }
            if (player) {
                playerService.setPlayerConnection(player->getId(),
                                                  message.conn.id);
                enqueueMessage(message.conn, LOGIN_SUCCESS);
                return player;
            }
        }

        enqueueMessage(message.conn, PLEASE_LOGIN);
        return nullptr;
    }
    return player;
}

void GameManager::processMessages(
    std::vector<connection::gameAndUserInterface> &messages) {
    static auto logger = logging::getLogger("GameManager::processMessages");

    for (const auto &message : messages) {
        enqueueMessage(message.conn, message.text);

        auto player = getPlayerFromLogin(message);
        logger->debug(std::to_string(message.conn.id) + ": " + message.text);

        if (!player)
            continue;

        // look up player's character
        // pointer is used as player may not have character yet
        auto characterId = playerService.playerToCharacter(player->getId());
        if (!characterId) {
            // create a new character for the player and add it to the game
            // state
            auto newCharacter =
                playerService.createPlayerCharacter(player->getId());
            newCharacter.set_isPlayerCharacter();
            gameState.addCharacter(newCharacter);
        }

        auto charController = playerService.playerToController(player->getId());

        if (!charController) {
            charController = playerService.createController(player->getId());
            characterId = playerService.playerToCharacter(player->getId());
            auto pCharacter = gameState.getCharacterFromLUT(*characterId);
            auto gameStatePtr = &gameState;
            charController->init(gameStatePtr, pCharacter, player);
        }

        charController->setCmdString(message.text);
        controllerQueue.push_back(charController);
    }
}

void GameManager::enqueueMessage(networking::Connection conn, std::string msg) {
    outgoingMessages.push({std::move(msg), conn});
}

void GameManager::sendMessagesToPlayers() {
    std::vector<connection::gameAndUserInterface> toSend;
    toSend.reserve(outgoingMessages.size());

    while (!outgoingMessages.empty()) {
        toSend.push_back(outgoingMessages.front());
        outgoingMessages.pop();
    }
    connectionManager.receiveFromGameManager(toSend);
    connectionManager.sendToServer();
}

void GameManager::enqueueAction(std::unique_ptr<Action> action) {
    // currentActionQueuePtr->push(std::move(action));
    nextAQueuePtr->push(std::move(action));
}

void GameManager::performQueuedActions() {
    while (!currentAQueuePtr->empty()) {
        currentAQueuePtr->front()->execute();
        currentAQueuePtr->pop();
    }
}

void GameManager::swapQueuePtrs() {
    std::swap(currentAQueuePtr, nextAQueuePtr);
}

void GameManager::addActionToQueue(std::unique_ptr<Action> action) {
    nextAQueuePtr->push(std::move(action));
}
GameState &GameManager::getState() { return gameState; }

void GameManager::sendCharacterMessage(UniqueId characterId,
                                       std::string message) {
    for(auto &controller : controllerQueue) {
        auto character = controller->getCharacter();
        if (character->getEntityId() == characterId) {

            auto player = controller->getPlayer();
            if(player != nullptr) {
                auto conn = networking::Connection{player->getConnectionId()};
                enqueueMessage(conn, std::move(message));
            }else {
               //do nothing

            }
        }
    }
}

PlayerService &GameManager::getPlayerService() { return playerService; }

void GameManager::haltServer() {
    logging::getLogger("GameManager::haltServer()")
        ->info("Shutting down server...");

    done = true;
}

void GameManager::swapCharacters(UniqueId casterCharacterId,
                                 UniqueId targetCharacterId) {
    auto casterPlayerId = playerService.characterToPlayer(casterCharacterId);
    auto targetPlayerId = playerService.characterToPlayer(targetCharacterId);
    playerService.updatePlayerCharacterMapping(casterPlayerId,
                                               targetCharacterId);
    playerService.updatePlayerCharacterMapping(targetPlayerId,
                                               casterCharacterId);
    // gameState.swapCharacters(casterCharacterId, targetCharacterId);
}

void GameManager::fetchCntrlCmds() {
    for(auto &controller : controllerQueue){
        if(controller->getCharacter() == nullptr) {
            //remove finished controllers
            controllerQueue.erase(std::remove(controllerQueue.begin(), controllerQueue.end(),
                                              controller),controllerQueue.end());
        }

        controller->update();
        auto msg = controller->getCmdString();
        if(!msg.empty()) {
            auto action =
                    commandParser.actionFromPlayerCommand(*controller, msg, *this);
            enqueueAction(std::move(action));
        }
    }
}
} // namespace gamemanager
} // namespace mudserver
