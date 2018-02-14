#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include "entities/ShopEntity.h"
#include "entities/AreaEntity.h"
#include "entities/DoorEntity.h"
#include "entities/NonPlayerCharacter.h"
#include "entities/ObjectEntity.h"
#include "entities/RoomEntity.h"
#include "Reset.h"

class YamlParser {

private:
    std::vector<YAML::Node> data; //holds all data nodes
    bool is_loaded = false;

    static std::string parseString(YAML::Node node);

    //calls constructors of each object and adds data to each respective object
    NonPlayerCharacter parseNPC(YAML::Node npcNode);
    ObjectEntity parseObject(YAML::Node objectNode);
    Reset parseReset(YAML::Node resetNode); //needs reset constructor
    void parseHelp(YAML::Node helpNode); //needs help constructor
    RoomEntity parseRoom(YAML::Node roomNode);
    ShopEntity parseShop(YAML::Node shopNode);
    DoorEntity parseDoor(YAML::Node doorNode);

    std::deque<RoomEntity> getAllRooms();
    //get all doors in the current room
    std::vector<DoorEntity> getAllDoors(YAML::Node roomNode);
    
public:
    //loads the YAML file into data (std::vector of YAML nodes)
    //each entity makes up one node in data (ex. "NPCs" make up one node)
    bool loadYamlFile(const std::string path);

    std::vector<NonPlayerCharacter> getAllNPCS();
    std::vector<ObjectEntity> getAllObjects();
    std::vector<Reset> getAllResets();
    void getAllHelps();
    std::vector<ShopEntity> getAllShops();
    AreaEntity getArea();
};

#endif
