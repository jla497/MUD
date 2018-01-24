#include "YamlParser.h"

int main(int argc, char* argv[]) {
    YamlParser parser{};
    const std::string path = "/lib/datafiles/detailed_mgoose.yml";
    bool is_loaded = parser.loadYamlFile(path);
    if(is_loaded) {
        parser.readAllNPCS();
    }
}