
#include "SpellParser.h"
#include "resources/SpellDataFields.h"
#include "Parser.h"

using namespace Parser;

bool SpellParser::loadYamlFile(const std::string &path) {
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

Spell SpellParser::parseSpell(YAML::Node node) const {
	Spell spell;
	if (node[EFFECT]) {
		spell.setEffect(parseString(node[EFFECT]));
	}
	if (node[MANA]) {
		spell.setMana(parseInt(node[MANA]));
	}
	if (node[MINLEVEL]) {
		spell.setMinLevel(parseUnsignedInt(node[MINLEVEL]));
	}
	if (node[NAME]) {
		spell.setName(parseString(node[NAME]));
	}
	if (node[DURATION]) {
		spell.setDuration(parseInt(node[DURATION]));
	}
	if (node[HITCHAR]) {
		spell.setHitChar(parseString(node[HITCHAR]));
	}
	if (node[HITROOM]) {
		spell.setHitRoom(parseString(node[HITROOM]));
	}
	if (node[HITVICT]) {
		spell.setHitVict(parseString(node[HITVICT]));
	}
	if (node[MISSROOM]) {
		spell.setMissRoom(parseString(node[MISSROOM]));
	}
	if (node[MISSCHAR]) {
		spell.setMissChar(parseString(node[MISSCHAR]));
	}
	if (node[DAMMSG]) {
		spell.setDammsg(parseString(node[DAMMSG]));
	}
	if (node[WEAROFF]) {
		spell.setWearoff(parseString(node[WEAROFF]));
	}
	if (node[IMMCHAR]) {
		spell.setImmchar(parseString(node[IMMCHAR]));
	}
	if (node[DAMAGE]) {
		spell.setDamage(parseString(node[DAMAGE])); 
	}
	return spell;
}

std::vector<Spell> SpellParser::getAllDefenseSpells() const {
	std::vector<Spell> defenseSpells;
	for (auto &document : data) {
		for (auto &node : document[DEFENSE]) {
			defenseSpells.push_back(parseSpell(node));
		}
	}
	return defenseSpells;
}

std::vector<Spell> SpellParser::getAllOffenseSpells() const {
	std::vector<Spell> offenseSpells;
	for (auto &document : data) {
		for (auto &node : document[OFFENSE]) {
			offenseSpells.push_back(parseSpell(node));
		}
	}
	return offenseSpells;
}

std::vector<Spell> SpellParser::getAllObjectSpells() const {
	std::vector<Spell> objectSpells;
	for (auto &document : data) {
		for (auto &node : document[OBJECT]) {
			objectSpells.push_back(parseSpell(node));
		}
	}
	return objectSpells;
}

std::vector<Spell> SpellParser::getAllOtherSpells() const {
	std::vector<Spell> otherSpells;
	for (auto &document : data) {
		for (auto &node : document[OTHER]) {
			otherSpells.push_back(parseSpell(node));
		}
	}
	return otherSpells;
}

std::vector<Spell> SpellParser::getAllPersonalSpells() const {
	std::vector<Spell> personalSpells;
	for (auto &document : data) {
		for (auto &node : document[PERSONAL]) {
			personalSpells.push_back(parseSpell(node));
		}
	}
	return personalSpells;
}
