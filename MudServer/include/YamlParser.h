#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include <vector>
#include <string>
#include "yaml-cpp/yaml.h"


class YamlParser {

private:
    std::vector<YAML::Node> data;
    bool is_loaded;
public:
    //loads the YAML file into data (std::vector of YAML nodes)
    //each entity makes up one node in data (ex. "NPCs" make up one node)
    bool loadYamlFile(const std::string path);
    
    //calls constructors of each object and adds data to each respective object
    void readNPCS();
    void readObjects();
    void readResets();
    void readRooms();
};

#endif