#include <string>
#include <vector>

#include "NPCEntity.h"

NPCEntity::NPCEntity(int armor, std::string& damage,
                     std::vector<std::string>& desc, unsigned int exp, int gold,
                     std::string& hit, unsigned int npcTypeId,
                     std::vector<std::string>& keywords, unsigned int level,
                     std::vector<std::string>& longDesc, std::string& shortDesc,
                     int thac0)

    : Entity::Entity(),
      m_armor(armor),
      m_damage(damage),
      m_desc(desc),
      m_exp(exp),
      m_gold(gold),
      m_hit(hit),
      m_npcTypeId(npcTypeId),
      m_keywords(keywords),
      m_level(level),
      m_longDesc(longDesc),
      m_shortDesc(shortDesc),
      m_thac0(thac0) {}
