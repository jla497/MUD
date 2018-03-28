
#include <algorithm>
#include <cassert>
#include <deque>

#include "YamlParser.h"
#include "parser.h"
#include "resources/DataFields.h"

using namespace parser;

bool YamlParser::loadYamlFile(const std::string &path) {
    if (is_loaded) {
        return false; // file is already loaded
    }
    data = YAML::LoadAllFromFile(path);

    if (data[0].IsNull()) {
        return false; // file was not found or file is empty
    }

    is_loaded = true;
    return true;
}

CharacterEntity YamlParser::parseNPC(const YAML::Node &npcNode) const {
    auto armor = npcNode[ARMOR].as<int>();
    auto damage = npcNode[DAMAGE].as<std::string>();

    std::vector<std::string> description;
    std::transform(npcNode[DESCRIPTION].begin(), npcNode[DESCRIPTION].end(),
                   std::back_inserter(description), parseString);

    auto exp = npcNode[EXP].as<unsigned int>();
    auto gold = npcNode[GOLD].as<int>();
    auto hit = npcNode[HIT].as<std::string>();
    auto npcTypeId = npcNode[ID].as<unsigned int>();

    std::vector<std::string> keywords;
    std::transform(npcNode[KEYWORDS].begin(), npcNode[KEYWORDS].end(),
                   std::back_inserter(keywords), parseString);

    auto level = npcNode[LEVEL].as<unsigned int>();

    std::vector<std::string> longdesc;
    std::transform(npcNode[LONGDESC].begin(), npcNode[LONGDESC].end(),
                   std::back_inserter(longdesc), parseString);

    std::string shortDesc = npcNode[SHORTDESC].as<std::string>();
    auto thac0 = npcNode[THAC0].as<int>();

    // FIXME this is WAY TOO MANY ARGUMENTS. this is a hint that you're doing
    // something wrong.
    return {armor,     damage,   description, exp,      gold,      hit,
            npcTypeId, keywords, level,       longdesc, shortDesc, thac0};
}

ObjectEntity YamlParser::parseObject(const YAML::Node &objectNode) const {
    std::vector<std::string> attributes;
    std::transform(objectNode[ATTRIBUTES].begin(), objectNode[ATTRIBUTES].end(),
                   std::back_inserter(attributes), parseString);

    auto cost = objectNode[COST].as<unsigned int>();

    std::vector<std::string> descExtra;
    std::vector<std::string> keywordsExtra;
    if (objectNode[EXTRA][DESC]) {
        std::transform(objectNode[EXTRA][DESC].begin(),
                       objectNode[EXTRA][DESC].end(),
                       std::back_inserter(descExtra), parseString);
    }
    if (objectNode[EXTRA][KEYWORDS]) {
        std::transform(objectNode[EXTRA][KEYWORDS].begin(),
                       objectNode[EXTRA][KEYWORDS].end(),
                       std::back_inserter(keywordsExtra), parseString);
    }

    auto objectTypeId = objectNode[ID].as<unsigned int>();
    auto itemType = objectNode[ITEM_TYPE].as<std::string>();

    std::vector<std::string> keywords;
    std::transform(objectNode[KEYWORDS].begin(), objectNode[KEYWORDS].end(),
                   std::back_inserter(keywords), parseString);

    std::vector<std::string> longdesc;
    std::transform(objectNode[LONGDESC].begin(), objectNode[LONGDESC].end(),
                   std::back_inserter(longdesc), parseString);

    auto shortdesc = objectNode[SHORTDESC].as<std::string>();

    std::vector<std::string> wearFlags;
    std::transform(objectNode[WEAR_FLAGS].begin(), objectNode[WEAR_FLAGS].end(),
                   std::back_inserter(wearFlags), parseString);

    auto weight = objectNode[WEIGHT].as<int>();

    return {attributes,   cost,      descExtra, keywordsExtra,
            objectTypeId, itemType,  keywords,  longdesc,
            shortdesc,    wearFlags, weight};
}

Reset YamlParser::parseReset(const YAML::Node &resetNode) const {
    auto id = resetNode[ID].as<int>();
    auto action = resetNode[ACTION].as<std::string>();

    std::string comment = "";
    if (resetNode[COMMENT]) {
        comment = resetNode[COMMENT].as<std::string>();
    }

    std::string state = "";
    if (resetNode[STATE]) {
        state = resetNode[STATE].as<std::string>();
    }

    int slot = -1;
    if (resetNode[SLOT]) {
        slot = resetNode[SLOT].as<int>();
    }

    int limit = -1;
    if (resetNode[LIMIT]) {
        limit = resetNode[LIMIT].as<int>();
    }

    int roomID = -1;
    if (resetNode[ROOM]) {
        roomID = resetNode[ROOM].as<int>();
    }
    return {id, action, comment, state, slot, limit, roomID};
}

void YamlParser::parseHelp(const YAML::Node &helpNode) const { (void)helpNode; }

DoorEntity YamlParser::parseDoor(const YAML::Node &doorNode) const {
    std::vector<std::string> desc;
    std::transform(doorNode[DESC].begin(), doorNode[DESC].end(),
                   std::back_inserter(desc), parseString);

    std::string dir = doorNode[DIR].as<std::string>();

    std::vector<std::string> keywords;
    std::transform(doorNode[KEYWORDS].begin(), doorNode[KEYWORDS].end(),
                   std::back_inserter(keywords), parseString);

    auto to = doorNode[TO].as<unsigned int>();

    return {desc, dir, keywords, to};
}

std::vector<DoorEntity> YamlParser::getAllDoors(const YAML::Node &roomNode) const {
    std::vector<DoorEntity> doors;
    // iterate through all doors in room and add them to list/vector of doors

    /*
     * FIXME:
     * If you made a DoorEntity implicitly constructable from a Node,
     * you could just do:
     *
     * return {roomNode[DOORS_ENT].begin(), roomNode[DOORS_ENT].end()};
     *
     * Iterators convert to Nodes convert to DoorEntities.
     * This can apply for every function that looks like this.
     */

    for (auto node : roomNode[DOORS_ENT]) {
        doors.push_back(parseDoor(node));
    }
    return doors;

}

RoomEntity YamlParser::parseRoom(const YAML::Node &roomNode) const {
    std::vector<std::string> desc;
    std::transform(roomNode[DESC].begin(), roomNode[DESC].end(),
                   std::back_inserter(desc), parseString);

    std::vector<DoorEntity> doors = getAllDoors(roomNode);

    std::vector<std::string> descExt;
    std::vector<std::string> keywordsExt;

    if (roomNode[EXTENDED_DESCRIPTIONS][DESC]) {
        std::transform(roomNode[EXTENDED_DESCRIPTIONS][DESC].begin(),
                       roomNode[EXTENDED_DESCRIPTIONS][DESC].end(),
                       std::back_inserter(descExt), parseString);
    }
    if (roomNode[EXTENDED_DESCRIPTIONS][KEYWORDS]) {
        std::transform(roomNode[EXTENDED_DESCRIPTIONS][KEYWORDS].begin(),
                       roomNode[EXTENDED_DESCRIPTIONS][KEYWORDS].end(),
                       std::back_inserter(keywordsExt), parseString);
    }

    auto name = roomNode[NAME].as<std::string>();
    auto roomId = roomNode[ID].as<unsigned int>();

    return {desc, doors, descExt, keywordsExt, name, roomId};
}

ShopEntity YamlParser::parseShop(const YAML::Node &shopNode) const {
    (void)shopNode;
    return {};
}

std::vector<CharacterEntity> YamlParser::getAllNPCS() const {
    std::vector<CharacterEntity> npcs;
    for (auto &document : data) {
        for (auto &node : document[NPCS_ENT]) {
            npcs.push_back(parseNPC(node));
        }
    }
    return npcs;
}

std::vector<ObjectEntity> YamlParser::getAllObjects() const {
    std::vector<ObjectEntity> objects;
    for (auto &node : data[0][OBJECTS_ENT]) {
        objects.push_back(parseObject(node));
    }
    return objects;
}

std::vector<Reset> YamlParser::getAllResets() const {
    std::vector<Reset> resets;
    for (auto &node : data[0][RESETS_ENT]) {
        resets.push_back(parseReset(node));
    }
    return resets;
}

void YamlParser::getAllHelps() const {}

std::vector<ShopEntity> YamlParser::getAllShops() const {
    std::vector<ShopEntity> shops;
    if (data[0][SHOPS_ENT]) {
        for (auto &node : data[0][SHOPS_ENT]) {
            shops.push_back(parseShop(node));
        }
    }
    return shops;
}

std::deque<RoomEntity> YamlParser::getAllRooms() const {
    std::deque<RoomEntity> rooms;
    for (auto &node : data[0][ROOMS_ENT]) {
        rooms.push_back(parseRoom(node));
    }
    return rooms;
}

AreaEntity YamlParser::getArea() const {
    auto rooms = getAllRooms();
    auto name = parseString(data[0][AREA_ENT][NAME]);
    AreaEntity area{name, rooms};
    return area;
}

mudserver::gamemanager::EntityFactory *YamlParser::makeFactory() {
    mudserver::gamemanager::EntityFactory *factory =
        new mudserver::gamemanager::EntityFactory(getAllNPCS(),
                                                  getAllObjects());
    return factory;
}