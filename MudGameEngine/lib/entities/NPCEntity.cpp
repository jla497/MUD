#include <string>
#include <vector>

#include "Entity.h"
#include "NPCEntity.h"

NPCEntity::NPCEntity(int armor, Roll damageRollData, std::string desc,
        unsigned int exp, int gold, Roll hitRollData, int npcTypeId, std::vector<std::string> keywords,
        unsigned int level, std::string longDesc, std::string shortDesc, int thac0) : 
    m_armor(armor),
    m_damageRollData(damageRollData),
    m_npcTypeId(npcTypeId),
    m_desc(desc),
    m_exp(exp),
    m_gold(gold),
    m_hitRollData(hitRollData),
    m_keywords(keywords),
    m_level(level),
    m_longDesc(longDesc),
    m_shortDesc(shortDesc),
    m_thac0(thac0) {
}

