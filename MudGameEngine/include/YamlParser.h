#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include "entities/AreaEntity.h"
#include "entities/CharacterEntity.h"
#include "entities/DoorEntity.h"
#include "entities/ObjectEntity.h"
#include "entities/RoomEntity.h"
#include "entities/ShopEntity.h"
#include "gamemanager/EntityFactory.h"
#include "reset/Reset.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

class YamlParser {

  private:
    std::vector<YAML::Node> data; // holds all data nodes
    bool is_loaded = false;

    // calls constructors of each object and adds data to each respective object
    CharacterEntity parseNPC(const YAML::Node &npcNode) const;
    ObjectEntity parseObject(const YAML::Node &objectNode) const;
    Reset parseReset(const YAML::Node &resetNode) const;
    void parseHelp(const YAML::Node &helpNode) const;
    RoomEntity parseRoom(const YAML::Node &roomNode) const;
    ShopEntity parseShop(const YAML::Node &shopNode) const;
    DoorEntity parseDoor(const YAML::Node &doorNode) const;

    std::deque<RoomEntity> getAllRooms() const;
    // get all doors in the current room
    std::vector<DoorEntity> getAllDoors(const YAML::Node &roomNode) const;

  public:
    // loads the YAML file into data (std::vector of YAML nodes)
    // each entity makes up one node in data (ex. "NPCs" make up one node)
    bool loadYamlFile(const std::string &path);
    std::vector<CharacterEntity> getAllNPCS() const;
    std::vector<ObjectEntity> getAllObjects() const;
    std::vector<Reset> getAllResets() const;
    void getAllHelps() const;
    std::vector<ShopEntity> getAllShops() const;
    AreaEntity getArea() const;
    mudserver::gamemanager::EntityFactory *makeFactory();
};

#endif
