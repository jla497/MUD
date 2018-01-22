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
    is_Loaded = true;
    return true;
}

void YamlParser::readNPCS(){
    //need NPC constructor
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





