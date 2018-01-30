#include <string>
#include <vector>

#include "NPCEntity.h"

NPCEntity::NPCEntity(UniqueId& id, int armor, std::vector<std::string>& desc,
                     unsigned int exp, int gold, int npcTypeId,
                     std::vector<std::string>& keywords, unsigned int level,
                     std::vector<std::string>& longDesc, std::string& shortDesc,
                     int thac0)

    : Entity::Entity(id),
      m_armor(armor),
      m_npcTypeId(npcTypeId),
      m_desc(desc),
      m_exp(exp),
      m_gold(gold),
      m_keywords(keywords),
      m_level(level),
      m_longDesc(longDesc),
      m_shortDesc(shortDesc),
      m_thac0(thac0) {}
