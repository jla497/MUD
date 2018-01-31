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

NPCEntity YamlParser::parseNPC(YAML::Node npcNode){

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

    NPCEntity npc = make_unique<NPCEntity>(id, armor, damage, 
        description, exp, gold, hit, npcTypeId,
        keywords, level, longdesc, shortDesc, thac0);

    return npc;
}

void YamlParser::parseObject(YAML::Node objectNode){

}

void YamlParser::parseReset(YAML::Node resetNode){

}

DoorEntity YamlParser::parseDoor(YAML::Node doorNode){
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

    DoorEntity door = make_unique<DoorEntity>(id, desc, dir, to);

    return door;
}

std::vector<DoorEntity> YamlParser::getAllDoors(YAML::Node roomNode){
    std::vector<DoorEntity> doors;
    //iterate through all doors in room and add them to list/vector of doors
    for (auto& doorNode : roomNode) {
        std::for_each(doorNode["doors"].begin(), document["doors"].end(), 
            [&doors](YAML::Node node){
                doors.push_back(parseDoor(node));
            });
    }

    return doors;

}

RoomEntity YamlParser::parseRoom(YAML::Node roomNode){
    RoomEntity(UniqueId& id, std::vector<std::string>& desc,
               std::vector<DoorEntity> doors, std::vector<std::string>& descExt,
               std::vector<std::string>& keywordsExt, std::string& name,
               unsigned int roomId);

    std::vector<std::string> description;
    std::for_each(roomNode["description"].begin(), roomNode["description"].end(),  
        [&description](YAML::Node line) {
            description.push_back(line.as<std::string>());
        });

    std::vector<DoorEntity> doors = getAllDoors(roomNode);

    RoomEntity room = make_unique<RoomEntity>(id, description, doors,);
}

void YamlParser::parseShop(YAML::Node shopNode){

}

void YamlParser::parseArea(YAML::Node areaNode){
    std::vector<RoomEntity> rooms = getAllRooms();
    std::string name = areaNode["name"].as<std::string>();
    AreaEntity area = make_unique<AreaEntity>(id, name, rooms);

    return area;
}

std::vector<NPCEntity> YamlParser::getAllNPCS(){
    std::vector<NPCEntity> npcs;
    //iterate through all npcs in data and add them to list/vector of npcs
    for (auto& document : data) {
        std::for_each(document["NPCS"].begin(), document["NPCS"].end(), 
            [&npcs](YAML::Node node){
                npcs.push_back(parseNPC(node));
            });
    }

    return npcs;
}

void YamlParser::getAllObjects(){
    //need Object constructor
}

void YamlParser::getAllResets(){
    //World original state?
}

void YamlParser::getAllRooms(){
    //need Room constructor
    std::vector<RoomEntity> rooms;
    //iterate through all rooms in data and add them to list/vector of rooms
    for (auto& document : data) {
        std::for_each(document["ROOMS"].begin(), document["ROOMS"].end(), 
            [&rooms](YAML::Node node){
                rooms.push_back(parseRoom(node));
            });
    }

    return rooms;
}

void YamlParser::getArea(){
    AreaEntity area;
    for (auto& document : data) {
        std::for_each(document["AREA"].begin(), document["AREA"].end().
            [&](Yaml::Node node){
                area = parseArea(node);
            });
    }

    return area;
}





