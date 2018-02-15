#ifndef NPC_H
#define NPC_H

#include "CharacterEntity.h"
#include "Roll.h"

// TODO: add character entity that derives from entity and then npc and player
// characters
// Reset is not entity

class NonPlayerCharacter : public CharacterEntity {
   private:
   	unsigned int m_npcTypeId{};

   public:
    NonPlayerCharacter(int armor, std::string damage,
              std::vector<std::string> desc, unsigned int exp, int gold,
              std::string hit, unsigned int npcTypeId,
              std::vector<std::string> keywords, unsigned int level,
              std::vector<std::string> longDesc, std::string shortDesc,
              int thac0);

    unsigned int getNpcTypeId() const;
};

#endif
