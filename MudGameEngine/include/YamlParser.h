#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include "NPCEntity.h"
#include "ObjectEntity.h"
#include "RoomEntity.h"
#include "ShopEntity.h"
#include "AreaEntity.h"
#include "DoorEntity.h"


class YamlParser {

private:
    std::vector<YAML::Node> data; //holds all data nodes
    bool is_loaded;

    //calls constructors of each object and adds data to each respective object
    std::unique_ptr<NPCEntity> parseNPC(YAML::Node npcNode);
    std::unique_ptr<ObjectEntity> parseObject(YAML::Node objectNode);
    void parseReset(YAML::Node resetNode); // needs reset constructor
    void parseHelp(YAML::Node helpNode); //need help constructor
    std::unique_ptr<RoomEntity> parseRoom(YAML::Node roomNode);
    std::unique_ptr<ShopEntity> parseShop(YAML::Node shopNode);
    std::unique_ptr<DoorEntity> parseDoor(YAML::Node doorNode); //gets all doors 

    std::vector<std::unique_ptr<RoomEntity>> getAllRooms();
    //gets all doorEntity objects in the given room
    std::vector<std::unique_ptr<DoorEntity>> getAllDoors(YAML::Node roomNode);
    
public:
    YamlParser();

    //loads the YAML file into data (std::vector of YAML nodes)
    //each entity makes up one node in data (ex. "NPCs" make up one node)
    bool loadYamlFile(const std::string path);

    //Returns vectors of respective entities 
    std::vector<std::unique_ptr<NPCEntity>> getAllNPCS();
    std::vector<std::unique_ptr<ObjectEntity>> getAllObjects();
    void getAllResets();
    void getAllHelps();
    std::vector<std::unique_ptr<ShopEntity>> getAllShops();
    std::unique_ptr<AreaEntity> getArea();
};

#endif
