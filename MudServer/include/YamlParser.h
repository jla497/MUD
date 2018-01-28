#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <yaml-cpp/yaml.h>


class YamlParser {

private:
    std::vector<YAML::Node> data; //holds all data nodes
    bool is_loaded;
public:
    YamlParser();

    //loads the YAML file into data (std::vector of YAML nodes)
    //each entity makes up one node in data (ex. "NPCs" make up one node)
    bool loadYamlFile(const std::string path);

    void readAllNPCS();

    //calls constructors of each object and adds data to each respective object
    void readNPC(YAML::Node npcs);
    void readObjects();
    void readResets();
    void readRooms();
    void readShops();
};

#endif
