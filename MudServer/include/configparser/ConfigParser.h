#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "Server.h"
#include <algorithm>
#include <boost/optional/optional.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

using networking::Port;

struct ConfigData {
    Port serverPort;
    std::string clientPort;
    std::string ymlFilePath;
    std::string url;
};

boost::optional<ConfigData> parseConfigFile(const std::string &filePath) {
    std::vector<YAML::Node> data;

    try {
        data = YAML::LoadAllFromFile(filePath);

    } catch (const std::exception &e) {
        std::cout << "something is wrong with the config file path or the file "
                     "doesn't exist...";
        // logger print error
        return boost::none;
    }

    // auto portNum = data[0]["SERVER"]["port"].as<unsigned int>();
    // std::cout<<"filepath:"<<data[0]["SERVER"]["yml_file"].as<std::string>();

    // Port port{portNum};

    ConfigData serverData{
        Port{data[0]["SERVER"]["port"].as<short unsigned int>()},
        data[0]["CLIENT"]["port"].as<std::string>(),
        data[0]["SERVER"]["yml_file"].as<std::string>(),
        data[0]["CLIENT"]["url"].as<std::string>()};

    return serverData;
};

#endif
