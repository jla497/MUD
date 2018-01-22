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

void YamlParser::readNPC(YAML::Node npcs){
    //need NPC constructor
    //variables below are temporary, will be used for testing purposes
    int armor = npcs["armor"].as<int>();
    double damage = npcs["damage"].as<double>();
    std::string description = npcs["description"].as<std::string>();
    int exp = npcs["exp"].as<int>();
    int gold = npcs["gold"].as<int>();
    int id = npcs["id"].as<int>();
    std::vector<std::string> keywords;
    for_each(npcs["keywords"].begin(), npcs["keywords"].end(), 
        [&keywords](YAML::Node keyword) {
            keywords.push_back(keyword.as<std::string>());
        });
    int level = npcs["level"].as<int>();
    std::string longdesc = npcs["longdesc"].as<std::string>();
    std::string shortdesc = npcs["shortdesc"].as<std::string>();
    int thac0 = npcs["thac0"].as<int>();

    std::cout << "Armor: " << armor << "\n";
}

void YamlParser::readObjects(){
    //need Object constructor
}
void YamlParser::readResets(){
    //World original state?
}
void YamlParser::readRooms(){
    //need Room constructor
}





