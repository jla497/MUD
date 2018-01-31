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
#include "UniqueId.h"


class YamlParser {

private:
    std::vector<YAML::Node> data; //holds all data nodes
    bool is_loaded;

    //calls constructors of each object and adds data to each respective object
    NPCEntity parseNPC(YAML::Node npcNode);
    ObjectEntity parseObject(YAML::Node objectNode);
    void parseReset(YAML::Node resetNode); // needs reset constructor
    RoomEntity parseRoom(YAML::Node roomNode);
    ShopEntity parseShop(YAML::Node shopNode);
    AreaEntity parseArea(YAML::Node areaNode);
    DoorEntity parseDoor(Yaml::Node doorNode); //gets all doors 
    //gets all doorEntity objects in the given room
    std::vector<DoorEntity> getAllDoors(Yaml::Node roomNode);
    
public:
    YamlParser();

    //loads the YAML file into data (std::vector of YAML nodes)
    //each entity makes up one node in data (ex. "NPCs" make up one node)
    bool loadYamlFile(const std::string path);

    //Returns vectors of respective entities 
    std::vector<NPCEntity> getAllNPCS();
    std::vector<ObjectEntity> getAllObjects();
    void getAllResets();
    std::vector<RoomEntity> getAllRooms();
    std::vector<ShopEntity> getAllShops();
    AreaEntity getArea();
};

#endif
