#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include "Reset.h"
#include "entities/AreaEntity.h"
#include "entities/DoorEntity.h"
#include "entities/NonPlayerCharacter.h"
#include "entities/ObjectEntity.h"
#include "entities/RoomEntity.h"
#include "entities/ShopEntity.h"
#include "gamemanager/EntityFactory.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

/*
 * FIXME
 * This class is basically just a namespace.
 * None of the parse* methods make use of `this`.
 */

class YamlParser {

  private:
    std::vector<YAML::Node> data; // holds all data nodes
    bool is_loaded = false;

    static std::string parseString(YAML::Node node);

    // calls constructors of each object and adds data to each respective object
    NonPlayerCharacter parseNPC(YAML::Node npcNode) const;
    ObjectEntity parseObject(YAML::Node objectNode) const;
    Reset parseReset(YAML::Node resetNode) const; // needs reset constructor
    void parseHelp(YAML::Node helpNode) const;    // needs help constructor
    RoomEntity parseRoom(YAML::Node roomNode) const;
    ShopEntity parseShop(YAML::Node shopNode) const;
    DoorEntity parseDoor(YAML::Node doorNode) const;

    std::deque<RoomEntity> getAllRooms() const;
    // get all doors in the current room
    std::vector<DoorEntity> getAllDoors(YAML::Node roomNode) const;

  public:
    // loads the YAML file into data (std::vector of YAML nodes)
    // each entity makes up one node in data (ex. "NPCs" make up one node)
<<<<<<< HEAD
    bool loadYamlFile(const std::string path);

    // Returns vectors of respective entities
    std::vector<std::unique_ptr<NonPlayerCharacter>> getAllNPCS();
    std::vector<std::unique_ptr<ObjectEntity>> getAllObjects();
    std::vector<std::unique_ptr<Reset>> getAllResets();
    void getAllHelps();
    std::vector<std::unique_ptr<ShopEntity>> getAllShops();
    std::unique_ptr<AreaEntity> getArea();
    mudserver::gamemanager::EntityFactory *makeFactory();
=======
    bool loadYamlFile(const std::string &path);

    std::vector<NonPlayerCharacter> getAllNPCS() const;
    std::vector<ObjectEntity> getAllObjects() const;
    std::vector<Reset> getAllResets() const;
    void getAllHelps() const;
    std::vector<ShopEntity> getAllShops() const;
    AreaEntity getArea() const;
>>>>>>> master
};

#endif
