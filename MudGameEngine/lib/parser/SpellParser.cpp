
#include "SpellParser.h"
#include "resources/DataFields.h"
#include "Parser.h"

namespace Parser {

bool YamlParser::loadYamlFile(const std::string &path) {
    if (is_loaded) {
        return false; // file is already loaded
    }
    data = YAML::LoadAllFromFile(path);

    if (data[0].IsNull()) {
        return false; // file was not found or file is empty
    }

    is_loaded = true;
    return true;
}

Spell parseSpell(YAML::Node node) const {
	std::string effect = "";
	if (node[EFFECT]) {
		effect = parseString(node[EFFECT]);
	}
	int mana = 0;
	if (node[MANA]) {
		mana = parseInt(node[MANA]);
	}
	unsigned int minlevel;
	if (node[MINLEVEL]) {
		minlevel = parseUnsignedInt(node[MINLEVEL]);
	}
	std::string name = "";
	if (node[NAME]) {
		name = parseString(node[NAME]);
	}
	int duration = 0;

}

} //namespace Parser