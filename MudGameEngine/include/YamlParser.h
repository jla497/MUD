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

    //calls constructors of each object and adds data to each respective object
    void parseNPC(YAML::Node npc);
    void parseObject(YAML::Node object);
    void parseReset(YAML::Node reset);
    void parseRoom(YAML::Node room);
    void parseShop(YAML::Node shop);
    void parseArea(YAML::Node area);
    
public:
    YamlParser();

    //loads the YAML file into data (std::vector of YAML nodes)
    //each entity makes up one node in data (ex. "NPCs" make up one node)
    bool loadYamlFile(const std::string path);

    //Returns vectors of respective entities 
    void getAllNPCS();
    void getAllObjects();
    void getAllResets();
    void getAllRooms();
    void getAllShops();
    void getArea();
};

#endif
