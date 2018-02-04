#ifndef CHARACTER_ENTITY_H
#define CHARACTER_ENTITY_H

#include "Entity.h"
#include "Roll.h"

class CharacterEntity : public Entity {
   private:
    int m_armor;
    std::string m_damage;  // TODO: string for now
    std::vector<std::string> m_desc;
    unsigned int m_exp;
    int m_gold;
    std::string m_hit;  // TODO: string for now    
    std::vector<std::string> m_keywords;
    unsigned int m_level;
    std::vector<std::string> m_longDesc;
    std::string m_shortDesc;
    int m_thac0;

    Roll m_damageRollData;  // ???
    Roll m_hitRollData;     // ???

   public:
    CharacterEntity(int armor, std::string& damage,
              std::vector<std::string>& desc, unsigned int exp, int gold,
              std::string& hit,
              std::vector<std::string>& keywords, unsigned int level,
              std::vector<std::string>& longDesc, std::string& shortDesc,
              int thac0);

    // std::string m_damage;

    // std::vector<std::string> m_desc;

    // unsigned int m_exp;

    // int m_gold;

    // std::string m_hit; 

    // unsigned int m_npcTypeId;

    // std::vector<std::string> m_keywords;

    // unsigned int m_level;

    // std::vector<std::string> m_longDesc;

    // std::string m_shortDesc;

    // int m_thac0;


};

#endif
