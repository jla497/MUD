#ifndef PLAYER_CHARACTER_ENTITY_H
#define PLAYER_CHARACTER_ENTITY_H

#include "entities/CharacterEntity.h"

class PlayerCharacterEntity : public CharacterEntity {
   private:
   	// Possibly race here later
   public:
    PlayerCharacterEntity(int armor, std::string& damage,
              std::vector<std::string>& desc, unsigned int exp, int gold,
              std::string& hit,
              std::vector<std::string>& keywords, unsigned int level,
              std::vector<std::string>& longDesc, std::string& shortDesc,
              int thac0);
};

#endif
