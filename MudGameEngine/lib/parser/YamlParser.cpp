#include "YamlParser.h"
#include "resources/DataFields.h"
#include <deque>

YamlParser::YamlParser() { is_loaded = false; }

bool YamlParser::loadYamlFile(const std::string path) {
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

std::string YamlParser::parseString(YAML::Node node) {
    return node.as<std::string>();
}

std::unique_ptr<NonPlayerCharacter> YamlParser::parseNPC(YAML::Node npcNode) {
    int armor = npcNode[ARMOR].as<int>();
    std::string damage = npcNode[DAMAGE].as<std::string>();

    std::vector<std::string> description;
    std::transform(npcNode[DESCRIPTION].begin(), npcNode[DESCRIPTION].end(),
                   std::back_inserter(description), parseString);

    unsigned int exp = npcNode[EXP].as<unsigned int>();
    int gold = npcNode[GOLD].as<int>();
    std::string hit = npcNode[HIT].as<std::string>();
    int npcTypeId = npcNode[ID].as<int>();

    std::vector<std::string> keywords;
    std::transform(npcNode[KEYWORDS].begin(), npcNode[KEYWORDS].end(),
                   std::back_inserter(keywords), parseString);

    unsigned int level = npcNode[LEVEL].as<unsigned int>();

    std::vector<std::string> longdesc;
    std::transform(npcNode[LONGDESC].begin(), npcNode[LONGDESC].end(),
                   std::back_inserter(longdesc), parseString);

    std::string shortDesc = npcNode[SHORTDESC].as<std::string>();
    int thac0 = npcNode[THAC0].as<int>();

    auto npc = std::make_unique<NonPlayerCharacter>(
        armor, damage, description, exp, gold, hit, npcTypeId, keywords, level,
        longdesc, shortDesc, thac0);

    return npc;
}

std::unique_ptr<ObjectEntity> YamlParser::parseObject(YAML::Node objectNode) {
    std::vector<std::string> attributes;
    std::transform(objectNode[ATTRIBUTES].begin(), objectNode[ATTRIBUTES].end(),
                   std::back_inserter(attributes), parseString);

    unsigned int cost = objectNode[COST].as<unsigned int>();

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

    unsigned int objectTypeId = objectNode[ID].as<unsigned int>();
    std::string itemType = objectNode[ITEM_TYPE].as<std::string>();

    std::vector<std::string> keywords;
    std::transform(objectNode[KEYWORDS].begin(), objectNode[KEYWORDS].end(),
                   std::back_inserter(keywords), parseString);

    std::vector<std::string> longdesc;
    std::transform(objectNode[LONGDESC].begin(), objectNode[LONGDESC].end(),
                   std::back_inserter(longdesc), parseString);

    std::string shortdesc = objectNode[SHORTDESC].as<std::string>();

    std::vector<std::string> wearFlags;
    std::transform(objectNode[WEAR_FLAGS].begin(), objectNode[WEAR_FLAGS].end(),
                   std::back_inserter(wearFlags), parseString);

    int weight = objectNode[WEIGHT].as<int>();

    auto object = std::make_unique<ObjectEntity>(
        attributes, cost, descExtra, keywordsExtra, objectTypeId, itemType,
        keywords, longdesc, shortdesc, wearFlags, weight);

    return object;
}

std::unique_ptr<Reset> YamlParser::parseReset(YAML::Node resetNode) {
    int id = resetNode[ID].as<int>();
    std::string action = resetNode[ACTION].as<std::string>();
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

    auto reset = std::make_unique<Reset>(id, action, comment, state, slot,
                                         limit, roomID);

    return reset;
}

void YamlParser::parseHelp(YAML::Node helpNode) {}

std::unique_ptr<DoorEntity> YamlParser::parseDoor(YAML::Node doorNode) {
    std::vector<std::string> desc;
    std::transform(doorNode[DESC].begin(), doorNode[DESC].end(),
                   std::back_inserter(desc), parseString);

    std::string dir = doorNode[DIR].as<std::string>();

    std::vector<std::string> keywords;
    std::transform(doorNode[KEYWORDS].begin(), doorNode[KEYWORDS].end(),
                   std::back_inserter(keywords), parseString);

    unsigned int to = doorNode[TO].as<unsigned int>();

    auto door = std::make_unique<DoorEntity>(desc, dir, keywords, to);

    return door;
}

std::vector<std::unique_ptr<DoorEntity>>
YamlParser::getAllDoors(YAML::Node roomNode) {
    std::vector<std::unique_ptr<DoorEntity>> doors;
    // iterate through all doors in room and add them to list/vector of doors

    std::for_each(
        roomNode[DOORS_ENT].begin(), roomNode[DOORS_ENT].end(),
        [&](YAML::Node node) { doors.push_back(std::move(parseDoor(node))); });

    return doors;
}

std::unique_ptr<RoomEntity> YamlParser::parseRoom(YAML::Node roomNode) {
    std::vector<std::string> desc;
    std::transform(roomNode[DESC].begin(), roomNode[DESC].end(),
                   std::back_inserter(desc), parseString);

    std::vector<std::unique_ptr<DoorEntity>> doors = getAllDoors(roomNode);

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

    std::string name = roomNode[NAME].as<std::string>();
    unsigned int roomId = roomNode[ID].as<unsigned int>();

    auto room = std::make_unique<RoomEntity>(desc, std::move(doors), descExt,
                                             keywordsExt, name, roomId);

    return room;
}

std::unique_ptr<ShopEntity> YamlParser::parseShop(YAML::Node shopNode) {
    auto shop = std::make_unique<ShopEntity>();
    return shop;
}

std::vector<std::unique_ptr<NonPlayerCharacter>> YamlParser::getAllNPCS() {
    std::vector<std::unique_ptr<NonPlayerCharacter>> npcs;
    for (auto &document : data) {
        std::for_each(document[NPCS_ENT].begin(), document[NPCS_ENT].end(),
                      [&](YAML::Node node) {
                          npcs.push_back(std::move(parseNPC(node)));
                      });
    }

    return npcs;
}

std::vector<std::unique_ptr<ObjectEntity>> YamlParser::getAllObjects() {
    std::vector<std::unique_ptr<ObjectEntity>> objects;
    for (auto &document : data) {
        std::for_each(document[OBJECTS_ENT].begin(),
                      document[OBJECTS_ENT].end(), [&](YAML::Node node) {
                          objects.push_back(std::move(parseObject(node)));
                      });
    }

    return objects;
}

std::vector<std::unique_ptr<Reset>> YamlParser::getAllResets() {
    std::vector<std::unique_ptr<Reset>> resets;
    for (auto &document : data) {
        std::for_each(document[RESETS_ENT].begin(), document[RESETS_ENT].end(),
                      [&](YAML::Node node) {
                          resets.push_back(std::move(parseReset(node)));
                      });
    }

    return resets;
}

void YamlParser::getAllHelps() {}

std::vector<std::unique_ptr<ShopEntity>> YamlParser::getAllShops() {
    std::vector<std::unique_ptr<ShopEntity>> shops;
    for (auto &document : data) {
        if (document[SHOPS_ENT]) {
            std::for_each(document[SHOPS_ENT].begin(),
                          document[SHOPS_ENT].end(), [&](YAML::Node node) {
                              shops.push_back(std::move(parseShop(node)));
                          });
        }
    }
    return shops;
}

std::deque<std::unique_ptr<RoomEntity>> YamlParser::getAllRooms() {
    // need Room constructor
    std::deque<std::unique_ptr<RoomEntity>> rooms;
    // iterate through all rooms in data and add them to list/vector of rooms
    for (auto &document : data) {
        std::for_each(document[ROOMS_ENT].begin(), document[ROOMS_ENT].end(),
                      [&](YAML::Node node) {
                          rooms.push_back(std::move(parseRoom(node)));
                      });
    }

    return rooms;
}

std::unique_ptr<AreaEntity> YamlParser::getArea() {
    std::unique_ptr<AreaEntity> area;
    auto rooms = getAllRooms();
    for (auto &document : data) {
        std::string name = document[AREA_ENT][NAME].as<std::string>();
        // TODO: remove std::move if looping over multiple dcouments
        area = std::make_unique<AreaEntity>(name, std::move(rooms));
    }
    return area;
}

mudserver::gamemanager::EntityFactory *YamlParser::makeFactory() {
    mudserver::gamemanager::EntityFactory *factory =
        new mudserver::gamemanager::EntityFactory(getAllNPCS());
    return factory;
}
