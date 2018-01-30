#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <iomanip>

#include "ConnectionManager.h"
#include "gamemanager/GameManager.h"

namespace mudserver {
namespace gamemanager {

using std::vector;

GameManager::GameManager() :
    connectionManager(),
    gameState(),
    players(),
    tick{kDefaultGameLoopTick} {}

/*
 * Runs a standard game loop, which consists of the following steps:
 *      - get user input (messages from the server)
 *      - update the game state using the input
 *      - render, i.e. send broadcast messages to players.
 */
void GameManager::mainLoop() {
    // TODO: Add a logging system
    std::cout << "Entered main game loop" << std::endl;

    bool done = false;
    using clock = std::chrono::system_clock;

    while (!done) {
        auto startTime = clock::now();
        auto tt = clock::to_time_t(startTime);
        std::cout << std::ctime(&tt) << std::endl;

        if (connectionManager.update()) {
            // An error was encountered, stop
            done = false;
            continue;
        }

        auto messages = connectionManager.sendToGameManager();

        processMessages(*messages);

        // send out updates
        // connectionManager.receiveFromGameManager(...)

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
    for (auto& message : messages) {
        // look up player from ID
        auto player = players.find(message->conn.id);
        // Player* player = nullptr;
        if (player == players.end()) {
            // We should add a login service that can deal with
            //      - players not existing
            //      - authenticating players
            std::cout << "Player not found" << std::endl;
            continue;
        }

        // look up player's character
        // pointer is used as player may not have character yet
        Character* character = player->second.getCharacter();
        if (!character) {
            // for now, we just continue, but we will want to allow new
            // character creation
            continue;
        }

        // look up character's location
        Room& room = gameState.getCharacterLocation(*character);


        //DEBUG - print the message text
        std::cout << message->text << std::endl;
        // parse message into verb/object
        // auto parsed = parsePlayerMessage(message.value);

        // then take action based on parse command
        // Command pattern - objects?
        // or just functions?

        // command = Command(gameState, parsed, character, room)
        // command.act()
    }
}

}  // namespace gamemanager
}  // namespace mudserver
