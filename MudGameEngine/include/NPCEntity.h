#ifndef NPC_ENTITY_H
#define NPC_ENTITY_H

#include "Entity.h"
#include "Roll.h"

// TODO: add character entity that derives from entity and then npc and player
// characters
// Reset is not entity

class NPCEntity : public Entity {
   private:
    int m_armor;
    unsigned int m_npcTypeId;  // what is this?
    std::string m_desc;
    unsigned int m_exp;
    int m_gold;
    std::vector<std::string> m_keywords;
    unsigned int m_level;
    std::vector<std::string> m_longDesc;
    std::string m_shortDesc;
    int m_thac0;
    Roll m_damageRollData;
    Roll m_hitRollData;

   public:
    NPCEntity(UniqueId& id, int armor, std::string& desc, unsigned int exp,
              int gold, int npcTypeId, std::vector<std::string>& keywords,
              unsigned int level, std::vector<std::string>& longDesc,
              std::string& shortDesc, int thac0);
};

#endif
