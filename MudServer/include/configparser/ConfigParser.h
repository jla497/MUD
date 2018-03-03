#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "Server.h"
#include "yaml-cpp/yaml.h"
#include <algorithm>
#include <boost/optional/optional.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using networking::Port;

struct ConfigData {
    Port serverPort;
    std::string clientPort;
    std::string ymlFilePath;
    std::string url;
};

boost::optional<ConfigData> parseConfigFile(const std::string filePath);

#endif
