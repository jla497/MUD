#ifndef NPCHARACTER_ENTITY_H
#define NPCHARACTER_ENTITY_H

#include "entities/CharacterEntity.h"

class NPCharacterEntity : public CharacterEntity {
   private:

   public:
    NPCharacterEntity(int armor, std::string& damage,
              std::vector<std::string>& desc, unsigned int exp, int gold,
              std::string& hit, unsigned int npcTypeId,
              std::vector<std::string>& keywords, unsigned int level,
              std::vector<std::string>& longDesc, std::string& shortDesc,
              int thac0);
};

#endif
