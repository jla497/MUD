// Server executable

#include <iostream>
#include <memory>
#include <sstream>
#include <unistd.h>
#include <boost/optional/optional.hpp>

#include "Server.h"
#include "connectionmanager/ConnectionManager.h"
#include "gamemanager/GameManager.h"
#include "logging.h"
#include "configparser/ConfigParser.h"
// #include "ConfigParser.h"

using networking::Port;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage:\n%s <port> [world file]\ne.g. %s 4002 mgoose.yml\n", argv[0], argv[0]);
        return 1;
    }

    auto configData = parseConfigFile(argv[1]);
    
    if(configData) {

       mudserver::logging::setLogLevel(mudserver::logging::LogLevel::debug);
       mudserver::connection::ConnectionManager connectionManager{configData->serverPort};
       mudserver::gamemanager::GameState gameState{};
       gameState.initFromYaml(configData->ymlFilePath);
    
       mudserver::gamemanager::GameManager gameManager{connectionManager, gameState};

       std::cout << "---------------------MUD Server Console---------------------"
              << std::endl;

       gameManager.mainLoop();

    } else {
        return -1;
    }
    
    return 0;    
    
}
