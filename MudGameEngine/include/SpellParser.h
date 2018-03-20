#ifndef SPELL_PARSER_H
#define SPELL_PARSER_H

#include "Spell.h"
#include <yaml-cpp/yaml.h>

class SpellParser {

  private:
    std::vector<YAML::Node> data; // holds all data nodes
    bool is_loaded = false;

    Spell parseSpell(const YAML::Node &node, Spell::SpellType type) const;

  public:
    // loads the YAML file into data (std::vector of YAML nodes)
    // each entity makes up one node in data (ex. "NPCs" make up one node)
    bool loadYamlFile(const std::string &path);

    std::vector<Spell> getAllSpells() const;
};

#endif
