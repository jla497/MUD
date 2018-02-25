#include <boost/format.hpp>
#include <boost/optional.hpp>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>
#include <vector>

#include "connectionmanager/ConnectionManager.h"
#include "entities/PlayerCharacter.h"
#include "gamemanager/GameManager.h"
#include "logging.h"

namespace mudserver {
namespace gamemanager {

using boost::format;
using boost::str;
using std::vector;

GameManager::GameManager(connection::ConnectionManager &connMan,
                         GameState &gameState)
    : connectionManager{connMan}, gameState{gameState},
      commandParser(), tick{DEFAULT_TICK_LENGTH_MS}, done{false},
      playerService(), outgoingMessages(), actions() {}

/**
 * Runs a standard game loop, which consists of the following steps:
 *      - get user input (messages from the server)
 *      - update the game state using the input
 *      - render, i.e. send broadcast messages to players.
 */
void GameManager::mainLoop() {
    static auto logger = logging::getLogger("GameManager::mainLoop");
    logger->info("Entered main game loop");

    using clock = std::chrono::high_resolution_clock;

    auto startTime = clock::now();

    while (!done) {
        unique_ptr<gameAndUserMsgs> messagesForConnMan;
        if (connectionManager.update()) {
            // An error was encountered, stop
            done = true;
            continue;
        }

        auto messages = connectionManager.sendToGameManager();

        processMessages(*messages);

        auto delta = clock::now() - startTime;
        if (delta >= tick) {
            startTime = clock::now();
            performQueuedActions();
            sendMessagesToPlayers();
        }
    }
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

void GameManager::processMessages(gameAndUserMsgs &messages) {
    static auto logger = logging::getLogger("GameManager::processMessages");

    for (auto &message : messages) {

        auto player = getPlayerFromLogin(*message);

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
            gameState.addCharacter(
                std::make_unique<PlayerCharacter>(std::move(newCharacter)));
        }
        auto &playerCharacterId =
            *playerService.playerToCharacter(player->getId());
        auto &playerCharacter =
            *gameState.getCharacterFromLUT(playerCharacterId);

        // parse message into verb/object
        std::unique_ptr<Action> action = commandParser.actionFromPlayerCommand(
            playerCharacter, message->text, *this);

        std::stringstream retMessage;
        // retMessage << "DEBUG: " << *action;

        enqueueAction(std::move(action));

        enqueueMessage(message->conn, retMessage.str());
    }
}

void GameManager::enqueueMessage(networking::Connection conn, std::string msg) {
    outgoingMessages.push({std::move(msg), conn});
}

void GameManager::sendMessagesToPlayers() {
    auto toSend = std::make_unique<gameAndUserMsgs>();

    while (!outgoingMessages.empty()) {
        toSend->push_back(std::make_unique<connection::gameAndUserInterface>(
            outgoingMessages.front()));
        outgoingMessages.pop();
    }
    connectionManager.receiveFromGameManager(std::move(toSend));
    connectionManager.sendToServer();
}

void GameManager::enqueueAction(unique_ptr<Action> action) {
    actions.push(std::move(action));
}
void GameManager::performQueuedActions() {
    while (!actions.empty()) {
        actions.front()->execute();
        actions.pop();
    }
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



} // namespace gamemanager
} // namespace mudserver
