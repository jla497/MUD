#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include "Reset.h"
#include "entities/AreaEntity.h"
#include "entities/DoorEntity.h"
#include "entities/CharacterEntity.h"
#include "entities/ObjectEntity.h"
#include "entities/RoomEntity.h"
#include "entities/ShopEntity.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

class YamlParser {

  private:
    std::vector<YAML::Node> data; // holds all data nodes
    bool is_loaded;

    static std::string parseString(YAML::Node node);

    // calls constructors of each object and adds data to each respective object
    std::unique_ptr<CharacterEntity> parseNPC(YAML::Node npcNode);
    std::unique_ptr<ObjectEntity> parseObject(YAML::Node objectNode);
    std::unique_ptr<Reset>
    parseReset(YAML::Node resetNode);    // needs reset constructor
    void parseHelp(YAML::Node helpNode); // need help constructor
    std::unique_ptr<RoomEntity> parseRoom(YAML::Node roomNode);
    std::unique_ptr<ShopEntity> parseShop(YAML::Node shopNode);
    std::unique_ptr<DoorEntity> parseDoor(YAML::Node doorNode); // gets all
                                                                // doors

    std::deque<std::unique_ptr<RoomEntity>> getAllRooms();
    // gets all doorEntity objects in the given room
    std::vector<std::unique_ptr<DoorEntity>> getAllDoors(YAML::Node roomNode);

  public:
    YamlParser();

    // loads the YAML file into data (std::vector of YAML nodes)
    // each entity makes up one node in data (ex. "NPCs" make up one node)
    bool loadYamlFile(const std::string path);

    // Returns vectors of respective entities
    std::vector<std::unique_ptr<CharacterEntity>> getAllNPCS();
    std::vector<std::unique_ptr<ObjectEntity>> getAllObjects();
    std::vector<std::unique_ptr<Reset>> getAllResets();
    void getAllHelps();
    std::vector<std::unique_ptr<ShopEntity>> getAllShops();
    std::unique_ptr<AreaEntity> getArea();
};

#endif
