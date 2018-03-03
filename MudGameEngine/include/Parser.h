#ifndef PARSER_H
#define PARSER_H

#include <yaml-cpp/yaml.h>

namespace Parser {

	std::string parseString(YAML::Node node) {
    	return node.as<std::string>();
	}

	int parseInt(YAML::Node node) {
		return node.as<int>();
	}

	unsigned int parseUnsignedInt(YAML::Node node) {
		return node.as<unsigned int>();
	}
}

#endif