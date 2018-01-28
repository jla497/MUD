#include "YamlParser.h"

int main(int argc, char* argv[]) {
	std::cout << "test 1 \n";
    YamlParser parser{};
    std::cout << "test\n";
    const std::string path = "./lib/dataFiles/detailed_mgoose.yml";
    parser.loadYamlFile(path);
    parser.readAllNPCS();

    return 0;
}