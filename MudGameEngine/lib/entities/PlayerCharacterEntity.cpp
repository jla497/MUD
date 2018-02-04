#include <string>
#include <vector>

#include "entities/PlayerCharacterEntity.h"

PlayerCharacterEntity::PlayerCharacterEntity(int armor, std::string& damage,
                     std::vector<std::string>& desc, unsigned int exp, int gold,
                     std::string& hit,
                     std::vector<std::string>& keywords, unsigned int level,
                     std::vector<std::string>& longDesc, std::string& shortDesc,
                     int thac0)

    : CharacterEntity::CharacterEntity(armor, damage, desc, exp, gold,
         hit, keywords, level, longDesc,
         shortDesc, thac0) {}
