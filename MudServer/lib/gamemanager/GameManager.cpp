#include <iomanip>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "connectionmanager/ConnectionManager.h"
#include "gamemanager/GameManager.h"
#include "logging.h"

namespace mudserver {
namespace gamemanager {

using std::vector;

GameManager::GameManager(connection::ConnectionManager &connMan)
    : connectionManager{connMan}, gameState(), players(), tick{kDefaultGameLoopTick} {}

/**
 * Runs a standard game loop, which consists of the following steps:
 *      - get user input (messages from the server)
 *      - update the game state using the input
 *      - render, i.e. send broadcast messages to players.
 */
void GameManager::mainLoop() {
    static auto logger = logging::getLogger("GameManager::mainLoop");
    logger->info("Entered main game loop");

    bool done = false;
    using clock = std::chrono::high_resolution_clock;

    while (!done) {
        auto startTime = clock::now();
        unique_ptr<gameAndUserMsgs> messagesForConnMan;

        if (connectionManager.update()) {
            // An error was encountered, stop
            done = true;
            continue;
        }

        auto messages = connectionManager.sendToGameManager();

        processMessages(*messages);

        sendMessagesToPlayers();

        auto delta = startTime - clock::now();

        if (tick > delta) {
            std::this_thread::sleep_for(tick - delta);
        } else {
            // TODO: report game too slow for tick
            // we have a problem - game can't update within tick cycle
        }
    }
}

void GameManager::processMessages(gameAndUserMsgs& messages) {
    static auto logger = logging::getLogger("GameManager::processMessages");
    for (auto& message : messages) {
        // look up player from ID
        auto playerId = message->conn.id;
        logger->debug(std::to_string(playerId) + ": " + message->text);

        if (players.find(playerId) == players.end()) {
            // We should add a login service that can deal with
            //      - players not existing
            //      - authenticating players
            players.emplace(
                playerId,
                Player{playerId, "player" + std::to_string(playerId), ""});
        }

        // Guaranteed not to throw out_of_range - Player has been created
        auto player = players.at(playerId);

        // look up player's character
        // pointer is used as player may not have character yet
        Character* character = player.getCharacter();
        if (character) {
            // look up character's location
//            Room& room = gameState.getCharacterLocation(*character);
        }

        // parse message into verb/object
        // auto parsed = parsePlayerMessage(message.value);

        // then take action based on parse command
        // Command pattern - objects?
        // or just functions?

        // command = Command(gameState, parsed, character, room)
        // command.act()

        enqueueMessage(message->conn, "You said " + message->text);
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

}  // namespace gamemanager
}  // namespace mudserver
