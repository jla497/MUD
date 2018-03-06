#include "parser.h"

std::string parser::parseString(YAML::Node node) {
    return node.as<std::string>();
}

int parser::parseInt(YAML::Node node) { return node.as<int>(); }

unsigned int parser::parseUnsignedInt(YAML::Node node) {
    return node.as<unsigned int>();
}