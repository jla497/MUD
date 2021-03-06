#ifndef PARSER_H
#define PARSER_H

#include <yaml-cpp/yaml.h>

namespace parser {

std::string parseString(YAML::Node node);

int parseInt(YAML::Node node);

unsigned int parseUnsignedInt(YAML::Node node);
} // namespace parser

#endif