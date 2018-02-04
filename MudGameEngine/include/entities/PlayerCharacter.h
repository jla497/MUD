#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "entities/Character.h"

class PlayerCharacter : public Character {
   private:
   	// Possibly race here later
   public:
    PlayerCharacter(int armor, std::string& damage,
              std::vector<std::string>& desc, unsigned int exp, int gold,
              std::string& hit,
              std::vector<std::string>& keywords, unsigned int level,
              std::vector<std::string>& longDesc, std::string& shortDesc,
              int thac0);
};

#endif
