#ifndef NPC_H
#define NPC_H

#include "entities/Character.h"

class NPC : public Character {
   private:
   	unsigned int m_npcTypeId;

   public:
    NPC(int armor, std::string& damage,
              std::vector<std::string>& desc, unsigned int exp, int gold,
              std::string& hit, unsigned int npcTypeId,
              std::vector<std::string>& keywords, unsigned int level,
              std::vector<std::string>& longDesc, std::string& shortDesc,
              int thac0);

    unsigned int getNpcTypeId() const;
};

#endif
