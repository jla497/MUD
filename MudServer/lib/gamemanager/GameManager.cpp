#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>
#include <vector>

#include <boost/optional.hpp>
#include <boost/format.hpp>

#include "connectionmanager/ConnectionManager.h"
#include "entities/CharacterEntity.h"
#include "gamemanager/GameManager.h"
#include "logging.h"
#include "persistence/PersistenceService.h"
#include "resources/PlayerCharacterDefaults.h"

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

    currentAQueuePtr = &actionsA;
    nextAQueuePtr = &actionsB;
    // point currentActionQueuePtr to actionQueueA
    // point nextActionQueuePtr to actionQueueB

    gameState.doReset();
    while (!done) {
        auto startTime = clock::now();

        if (connectionManager.update()) {
            // An error was encountered, stop
            done = true;
            continue;
        }

        auto messages = connectionManager.sendToGameManager();

        processMessages(messages);

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

boost::optional<Player &>
GameManager::getPlayerFromLogin(const gameAndUserInterface &message) {
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
        return boost::none;
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
            gameState.addCharacter(newCharacter);
        }

        // parse message into verb/object
        auto action =
            commandParser.actionFromPlayerCommand(*player, message.text, *this);

        enqueueAction(std::move(action));
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
    auto playerId = playerService.characterToPlayer(characterId);
    auto player = playerService.getPlayerById(playerId);
    if (player) {
        auto conn = networking::Connection{player->getConnectionId()};
        enqueueMessage(conn, std::move(message));
    }
}

PlayerService &GameManager::getPlayerService() { return playerService; }

void GameManager::haltServer() {
    logging::getLogger("GameManager::haltServer()")
        ->info("Shutting down server...");
    done = true;
}

} // namespace gamemanager
} // namespace mudserver
