#include "Parser.h"

std::string Parser::parseString(YAML::Node node) {
    return node.as<std::string>();
}

int Parser::parseInt(YAML::Node node) { return node.as<int>(); }

unsigned int Parser::parseUnsignedInt(YAML::Node node) {
    return node.as<unsigned int>();
}