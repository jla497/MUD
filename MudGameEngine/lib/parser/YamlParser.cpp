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

void YamlParser::parseNPC(YAML::Node npc){
    //need NPC constructor
    //variables below are temporary, will be used for testing purposes
    int armor = npc["armor"].as<int>();
    std::string damage = npc["damage"].as<std::string>();
    
    std::vector<std::string> description;
    std::for_each(npc["description"].begin(), npc["description"].end(),
        [&description](YAML::Node line) {
            description.push_back(line.as<std::string>());
        });
        
    int exp = npc["exp"].as<int>();
    int gold = npc["gold"].as<int>();
    std::string hit = npc["hit"].as<std::string>();
    int id = npc["id"].as<int>();
    
    std::vector<std::string> keywords;
    std::for_each(npc["keywords"].begin(), npc["keywords"].end(), 
        [&keywords](YAML::Node keyword) {
            keywords.push_back(keyword.as<std::string>());
        });

    
    int level = npc["level"].as<int>();

    std::vector<std::string> longdesc;
    std::for_each(npc["longdesc"].begin(), npc["longdesc"].end(),  
        [&longdesc](YAML::Node line) {
            longdesc.push_back(line.as<std::string>());
        });

    std::string shortdesc = npc["shortdesc"].as<std::string>();
    int thac0 = npcs["thac0"].as<int>();
}

void parseNPC(YAML::Node npc){

}

void parseObject(YAML::Node object){

}

void parseReset(YAML::Node reset){

}

void parseRoom(YAML::Node room){

}

void parseShop(YAML::Node shop){

}

void parseArea(YAML::Node area){

}

void YamlParser::getAllNPCS(){
    //need NPC Object
    //iterate through all npcs in data and add them to list/vector of npcs
    for (auto& document : data) {
        std::for_each(document["NPCS"].begin(), document["NPCS"].end(), 
            [&](YAML::Node node){
                readNPC(node);
            });
    }
}

void YamlParser::getAllObjects(){
    //need Object constructor
}

void YamlParser::getAllResets(){
    //World original state?
}

void YamlParser::getAllRooms(){
    //need Room constructor
}

void YamlParser::getArea(){

}





