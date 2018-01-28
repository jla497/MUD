#ifndef NPCEntity_H
#define NPCEntity_H
#include <string>
#include <vector>

#include "Roll.h"
#include "Entity.h"

class NPCEntity : public Entity {
private:
    int             m_armor;
    Roll            m_damageRollData;
    int             m_npcTypeId; // what is this?
    std::string     m_desc;
    unsigned int    m_exp;
    int             m_gold;
    Roll            m_hitRollData;
    std::vector<std::string>    m_keywords;
    unsigned int    m_level;
    std::string     m_longDesc;
    std::string     m_shortDesc; // isn't this the same as desc?
    int             m_thac0;
public:
   NPCEntity(int armor, Roll damageRollData, std::string desc,
             unsigned int exp, int gold, Roll hitRollData, int npcTypeId, std::vector<std::string> keywords,
             unsigned int level, std::string longDesc, std::string shortDesc,
             int thac0);
};

#endif
