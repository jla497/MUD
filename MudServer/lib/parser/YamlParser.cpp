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
    std::string damage = npcs["damage"].as<std::string>();
    
    std::vector<std::string> description;
    std::for_each(npcs["description"].begin(), npcs["description"].end(),
        [&description](YAML::Node line) {
            description.push_back(line.as<std::string>());
        });
        
    int exp = npcs["exp"].as<int>();
    int gold = npcs["gold"].as<int>();
    std::string hit = npcs["hit"].as<std::string>();
    int id = npcs["id"].as<int>();
    
    std::vector<std::string> keywords;
    std::for_each(npcs["keywords"].begin(), npcs["keywords"].end(), 
        [&keywords](YAML::Node keyword) {
            keywords.push_back(keyword.as<std::string>());
        });

    
    int level = npcs["level"].as<int>();

    std::vector<std::string> longdesc;
    std::for_each(npcs["longdesc"].begin(), npcs["longdesc"].end(),  
        [&longdesc](YAML::Node line) {
            longdesc.push_back(line.as<std::string>());
        });

    std::string shortdesc = npcs["shortdesc"].as<std::string>();
    int thac0 = npcs["thac0"].as<int>();
}

void YamlParser::readAllNPCS(){
    //need NPC Object
    //iterate through all npcs in data and add them to list/vector of npcs
    for (auto& document : data) {
        std::for_each(document["NPCS"].begin(), document["NPCS"].end(), 
            [&](YAML::Node node){
                readNPC(node);
            });
    }
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





