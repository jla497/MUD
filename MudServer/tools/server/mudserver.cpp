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
        printf("Usage:\n%s <port>\ne.g. %s 4002\n", argv[0], argv[0]);
        return 1;
    }

    Port port{(Port)std::stoi(argv[1])};
    mudserver::logging::setLogLevel(mudserver::logging::LogLevel::debug);

    mudserver::connection::ConnectionManager connectionManager{port};
    mudserver::gamemanager::GameManager gameManager{connectionManager};

    std::cout << "---------------------MUD Server Console---------------------"
              << std::endl;

    gameManager.mainLoop();

    return 0;
}
