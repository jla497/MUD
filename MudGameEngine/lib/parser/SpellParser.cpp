
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
	Spell spell();
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

std::vector<Spell> getAllDefenseSpells() const {
	std::vector<Spell> defenseSpells;
	for (auto &node : data[DEFENSE]) {
		defenseSpells.push_back(parseSpell(node));
	}
}

std::vector<Spell> getAllOffenseSpells() const {
	std::vector<Spell> offenseSpells;
	for (auto &node : data[OFFENSE]) {
		offenseSpells.push_back(parseSpell(node));
	}
}

std::vector<Spell> getAllObjectSpells() const {
	std::vector<Spell> objectSpells;
	for (auto &node : data[OBJECT]) {
		objectSpells.push_back(parseSpell(node));
	}
}

std::vector<Spell> getAllOtherSpells() const {
	std::vector<Spell> otherSpells;
	for (auto &node : data[OTHER]) {
		otherSpells.push_back(parseSpell(node));
	}
}

std::vector<Spell> getAllPersonalSpells() const {
	std::vector<Spell> personalSpells;
	for (auto &node : data[PERSONAL]) {
		personalSpells.push_back(parseSpell(node));
	}
}

} //namespace Parser