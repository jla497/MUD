#include "configparser/ConfigParser.h"

boost::optional<ConfigData> parseConfigFile(const std::string filePath) {
    std::vector<YAML::Node> data;
    
    try {
        data = YAML::LoadAllFromFile(filePath);

    } catch (const std::exception &e) {
        std::cout << "something is wrong with the config file path or the file "
                     "doesn't exist...";
        // logger print error
        return boost::none;
    }

    // auto serverPort = data["server-port"].as<short unsigned int>();
    // auto clientPort = data["CLIENT"]["port"].as<std::string>();
    // auto ymlFile = data["SERVER"]["yml_file"].as<std::string>();
    // auto url = data["CLIENT"]["url"].as<std::string>();
    // ConfigData serverData{
    //     Port{serverPort},
    //     clientPort,
    //     ymlFile,
    //     url
    //     };
    ConfigData serverData{
        Port{4000},
        "4000",
        "../build/MudGameEngine/lib/dataFiles/detailed_smurf.yml",
        "localhost"
        };

    return serverData;
};