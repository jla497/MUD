#include "configparser/ConfigParser.h"

boost::optional<ConfigData> parseConfigFile(const std::string filePath) {
    std::vector<YAML::Node> config;
    try {
        config = YAML::LoadAllFromFile(filePath);

    } catch (const std::exception &e) {
        std::cout << "something is wrong with the config file path or the file "
                     "doesn't exist...";
        // logger print error
        return boost::none;
    }

    auto serverPort = config[0]["SERVER"]["port"].as<short unsigned int>();
    auto clientPort = config[0]["CLIENT"]["port"].as<std::string>();
    auto areas = config[0]["SERVER"]["areas"].as<std::vector<std::string>>();
    auto spells = config[0]["SERVER"]["spells"].as<std::string>();
    auto configDir = config[0]["SERVER"]["config_dir"].as<std::string>();
    auto url = config[0]["CLIENT"]["url"].as<std::string>();

    ConfigData serverData{Port{serverPort}, clientPort, areas,
                          spells,           configDir,  url};
    return serverData;
};