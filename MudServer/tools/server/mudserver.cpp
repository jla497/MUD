// Server executable

#include <boost/optional/optional.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <unistd.h>

#include "Server.h"
#include "configparser/ConfigParser.h"
#include "connectionmanager/ConnectionManager.h"
#include "gamemanager/GameManager.h"
#include "i18n/i18n.h"
#include "logging.h"

using networking::Port;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage:\n%s <config_file>\ne.g. %s mudconfig.yml\n", argv[0],
               argv[0]);
        return 1;
    }

    i18n::init();

    auto configData = parseConfigFile(argv[1]);

    if (configData) {

        mudserver::logging::setLogLevel(mudserver::logging::LogLevel::debug);

        mudserver::connection::ConnectionManager connectionManager{
            configData->serverPort};

        mudserver::persistence::PersistenceService persistenceService{
            configData->configDir};
        mudserver::gamemanager::GameState gameState =
            persistenceService.loadGameState();
        gameState.initFromYaml(configData->areas, configData->spells);

        mudserver::gamemanager::GameManager gameManager{
            connectionManager, gameState, persistenceService};

        std::cout
            << "---------------------MUD Server Console---------------------"
            << std::endl;

        gameManager.mainLoop();

    } else {
        return -1;
    }

    return 0;
}
