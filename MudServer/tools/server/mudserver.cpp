// Server executable

#include <iostream>
#include <memory>
#include <sstream>
#include <unistd.h>

#include "Server.h"
#include "connectionmanager/ConnectionManager.h"
#include "gamemanager/GameManager.h"
#include "logging.h"

using networking::Port;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage:\n%s <port> [world file]\ne.g. %s 4002 mgoose.yml\n", argv[0], argv[0]);
        return 1;
    }

    Port port{(Port)std::stoi(argv[1])};
    mudserver::logging::setLogLevel(mudserver::logging::LogLevel::debug);

    mudserver::connection::ConnectionManager connectionManager{port};
    mudserver::gamemanager::GameState gameState{};
    if (argc > 2) {
        /*
         * FIXME
         * Nick might very well make us connect YAML worlds together.
         * Do not design around only 1 YAML world existing at a time.
         */
        gameState.initFromYaml(argv[2]);
    }
    mudserver::gamemanager::GameManager gameManager{connectionManager, gameState};

    std::cout << "---------------------MUD Server Console---------------------"
              << std::endl;

    gameManager.mainLoop();

    return 0;
}
