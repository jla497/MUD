
#include "SpellParser.h"
#include "parser.h"
#include "resources/SpellDataFields.h"

using namespace parser;

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

Spell SpellParser::parseSpell(const YAML::Node &node,
                              Spell::SpellType type) const {
    Spell spell;
    if (node[EFFECT]) {
        spell.setEffect(parseString(node[EFFECT]));
    }
    if (node[MANA]) {
        spell.setMana(parseUnsignedInt(node[MANA]));
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

    Spell::DisplayMessages messages;
    if (node[HITCHAR]) {
        messages.hitchar = parseString(node[HITCHAR]);
    }
    if (node[HITROOM]) {
        messages.hitroom = parseString(node[HITROOM]);
    }
    if (node[HITVICT]) {
        messages.hitvict = parseString(node[HITVICT]);
    }
    if (node[MISSROOM]) {
        messages.missroom = parseString(node[MISSROOM]);
    }
    if (node[MISSCHAR]) {
        messages.misschar = parseString(node[MISSCHAR]);
    }
    if (node[MISSVICT]) {
        messages.missvict = parseString(node[MISSVICT]);
    }
    spell.setDisplayMessages(messages);

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
    spell.setType(type);
    return spell;
}

std::vector<Spell> SpellParser::getAllSpells() const {
    std::vector<Spell> spells;
    for (auto &node : data[0][DEFENSE]) {
        spells.push_back(parseSpell(node, Spell::SpellType::defense));
    }
    for (auto &node : data[0][OFFENSE]) {
        spells.push_back(parseSpell(node, Spell::SpellType::offense));
    }
    for (auto &node : data[0][OBJECT]) {
        spells.push_back(parseSpell(node, Spell::SpellType::object));
    }
    for (auto &node : data[0][PERSONAL]) {
        spells.push_back(parseSpell(node, Spell::SpellType::personal));
    }
    for (auto &node : data[0][OTHER]) {
        spells.push_back(parseSpell(node, Spell::SpellType::other));
    }
    return spells;
}
