#include "YamlParser.h"

YamlParser::YamlParser() {
    is_loaded = false;
}

bool YamlParser::loadYamlFile(const std::string path){
    if (is_loaded) {
        return false; //file is already loaded
    }
    data = YAML::LoadAllFromFile(path);

    if (data[0].IsNull()){
        return false; //file was not found or file is empty
    }

    is_loaded = true;
    return true;
}

std::unique_ptr<NPCEntity> YamlParser::parseNPC(YAML::Node npcNode){
    int armor = npcNode["armor"].as<int>();
    std::string damage = npcNode["damage"].as<std::string>();
    
    std::vector<std::string> description;
    std::for_each(npcNode["description"].begin(), npcNode["description"].end(),
        [&description](YAML::Node line) {
            description.push_back(line.as<std::string>());
        });
        
    unsigned int exp = npcNode["exp"].as<unsigned int>();
    int gold = npcNode["gold"].as<int>();
    std::string hit = npcNode["hit"].as<std::string>();
    int npcTypeId = npcNode["id"].as<int>();
    
    std::vector<std::string> keywords;
    std::for_each(npcNode["keywords"].begin(), npcNode["keywords"].end(), 
        [&keywords](YAML::Node keyword) {
            keywords.push_back(keyword.as<std::string>());
        });
    
    unsigned int level = npcNode["level"].as<unsigned int>();

    std::vector<std::string> longDesc;
    std::for_each(npcNode["longdesc"].begin(), npcNode["longdesc"].end(),  
        [&longDesc](YAML::Node line) {
            longDesc.push_back(line.as<std::string>());
        });

    std::string shortDesc = npcNode["shortdesc"].as<std::string>();
    int thac0 = npcNode["thac0"].as<int>();

    auto npc = std::make_unique<NPCEntity>(armor, damage, 
        description, exp, gold, hit, npcTypeId,
        keywords, level, longDesc, shortDesc, thac0);

    return npc;
}

std::unique_ptr<ObjectEntity> YamlParser::parseObject(YAML::Node objectNode){
    std::vector<std::string> attributes;
    std::for_each(objectNode["attributes"].begin(), objectNode["attributes"].end(),  
        [&attributes](YAML::Node line) {
            attributes.push_back(line.as<std::string>());
        });

    unsigned int cost = objectNode["cost"].as<unsigned int>();

    std::vector<std::string> descExtra;
    std::vector<std::string> keywordsExtra;
    if(objectNode["extra"]["desc"]) {
        std::for_each(objectNode["extra"]["desc"].begin(), 
            objectNode["extra"]["desc"].end(),  
            [&descExtra](YAML::Node line) {
                descExtra.push_back(line.as<std::string>());
            });
    }
    if(objectNode["extra"]["keywords"]) {
        std::for_each(objectNode["extra"]["keywords"].begin(), 
            objectNode["extra"]["keywords"].end(),  
            [&keywordsExtra](YAML::Node line) {
                keywordsExtra.push_back(line.as<std::string>());
            });
    }

    unsigned int objectTypeId = objectNode["id"].as<unsigned int>();
    std::string itemType = objectNode["item_type"].as<std::string>();

    std::vector<std::string> keywords;
    std::for_each(objectNode["keywords"].begin(), objectNode["keywords"].end(),  
        [&keywords](YAML::Node line) {
            keywords.push_back(line.as<std::string>());
        });

    std::vector<std::string> longDesc;
    std::for_each(objectNode["longdesc"].begin(), objectNode["longdesc"].end(),  
        [&longDesc](YAML::Node line) {
            longDesc.push_back(line.as<std::string>());
        });

    std::string shortDesc = objectNode["shortdesc"].as<std::string>();

    std::vector<std::string> wearFlags;
    std::for_each(objectNode["wear_flags"].begin(), objectNode["wear_flags"].end(),  
        [&wearFlags](YAML::Node line) {
            wearFlags.push_back(line.as<std::string>());
        });

    int weight = objectNode["weight"].as<int>();

    auto object = std::make_unique<ObjectEntity>(attributes, cost, descExtra, 
        keywordsExtra, objectTypeId, itemType, keywords, longDesc, shortDesc, wearFlags, weight);

    return object;
}

void YamlParser::parseReset(YAML::Node resetNode){

}

void YamlParser::parseHelp(YAML::Node helpNode){

}

std::unique_ptr<DoorEntity> YamlParser::parseDoor(YAML::Node doorNode){
    std::vector<std::string> desc;
    std::for_each(doorNode["desc"].begin(), doorNode["desc"].end(),  
        [&desc](YAML::Node line) {
            desc.push_back(line.as<std::string>());
        });

    std::string dir = doorNode["dir"].as<std::string>();

    std::vector<std::string> keywords;
    std::for_each(doorNode["keywords"].begin(), doorNode["keywords"].end(),  
        [&keywords](YAML::Node line) {
            keywords.push_back(line.as<std::string>());
        });

    unsigned int to = doorNode["to"].as<unsigned int>();

    auto door = std::make_unique<DoorEntity>(desc, dir, keywords, to);

    return door;
}

std::vector<std::unique_ptr<DoorEntity>> YamlParser::getAllDoors(YAML::Node roomNode){
    std::vector<std::unique_ptr<DoorEntity>> doors;
    //iterate through all doors in room and add them to list/vector of doors

    std::for_each(roomNode["doors"].begin(), roomNode["doors"].end(),
        [&](YAML::Node node){
            doors.push_back(std::move(parseDoor(node)));
        });
/*
    for (auto& doorNode : roomNode) {
        std::for_each(doorNode["doors"].begin(), document["doors"].end(), 
            [&doors](YAML::Node node){
                doors.push_back(parseDoor(node));
            });
    }
    */

    return doors;
}

std::unique_ptr<RoomEntity> YamlParser::parseRoom(YAML::Node roomNode){
    std::vector<std::string> description;
    std::for_each(roomNode["description"].begin(), roomNode["description"].end(),  
        [&description](YAML::Node line) {
            description.push_back(line.as<std::string>());
        });

    std::vector<std::unique_ptr<DoorEntity>> doors = getAllDoors(roomNode);

    std::vector<std::string> descExt;
    std::vector<std::string> keywordsExt;
    if(roomNode["extended_descriptions"]["desc"]) {
        std::for_each(roomNode["extended_descriptions"]["desc"].begin(), 
            roomNode["extended_descriptions"]["desc"].end(),  
            [&descExt](YAML::Node line) {
                descExt.push_back(line.as<std::string>());
            });
    }
    if(roomNode["extended_descriptions"]["keywords"]) {
        std::for_each(roomNode["extended_descriptions"]["keywords"].begin(), 
            roomNode["extended_descriptions"]["keywords"].end(),  
            [&keywordsExt](YAML::Node line) {
                keywordsExt.push_back(line.as<std::string>());
            });
    }

    std::string name = roomNode["name"].as<std::string>();
    unsigned int roomId = roomNode["id"].as<unsigned int>();

    auto room = std::make_unique<RoomEntity>(description, std::move(doors), descExt,
        keywordsExt, name, roomId);

    return room;
}

std::unique_ptr<ShopEntity> YamlParser::parseShop(YAML::Node shopNode){
    auto shop = std::make_unique<ShopEntity>();
    return shop;
}

std::unique_ptr<AreaEntity> YamlParser::parseArea(YAML::Node areaNode){
    std::vector<std::unique_ptr<RoomEntity>> rooms = getAllRooms();
    std::string name = areaNode["name"].as<std::string>();
    auto area = std::make_unique<AreaEntity>(name, std::move(rooms));

    return area;
}

std::vector<std::unique_ptr<NPCEntity>> YamlParser::getAllNPCS(){
    std::vector<std::unique_ptr<NPCEntity>> npcs;
    for (auto& document : data) {
        std::for_each(document["NPCS"].begin(), document["NPCS"].end(), 
            [&](YAML::Node node){
                npcs.push_back(std::move(parseNPC(node)));
            });
    }

    return npcs;
}

std::vector<std::unique_ptr<ObjectEntity>> YamlParser::getAllObjects(){
    std::vector<std::unique_ptr<ObjectEntity>> objects;
    for (auto& document : data) {
        std::for_each(document["OBJECTS"].begin(), document["OBJECTS"].end(), 
            [&](YAML::Node node){
                objects.push_back(std::move(parseObject(node)));
            });
    }

    return objects;
}

void YamlParser::getAllResets(){
    //World original state?
}

void YamlParser::getAllHelps(){

}

std::vector<std::unique_ptr<ShopEntity>> YamlParser::getAllShops(){
    std::vector<std::unique_ptr<ShopEntity>> shops;
    for (auto& document : data) {
        std::for_each(document["SHOPS"].begin(), document["SHOPS"].end(), 
            [&](YAML::Node node){
                shops.push_back(std::move(parseShop(node)));
            });
    }

    return shops;
}

std::vector<std::unique_ptr<RoomEntity>> YamlParser::getAllRooms(){
    //need Room constructor
    std::vector<std::unique_ptr<RoomEntity>> rooms;
    //iterate through all rooms in data and add them to list/vector of rooms
    for (auto& document : data) {
        std::for_each(document["ROOMS"].begin(), document["ROOMS"].end(), 
            [&](YAML::Node node){
                rooms.push_back(std::move(parseRoom(node)));
            });
    }

    return rooms;
}

std::unique_ptr<AreaEntity> YamlParser::getArea(){
    std::unique_ptr<AreaEntity> area;
    for (auto& document : data) {
        std::for_each(document["AREA"].begin(), document["AREA"].end(),
            [&](YAML::Node node){
                area = parseArea(std::move(node));
            });
    }

    return area;
}





