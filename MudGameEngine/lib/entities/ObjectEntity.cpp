#include <string>
#include <vector>

#include "ObjectEntity.h"

ObjectEntity::ObjectEntity(std::vector<std::string>& attribute, unsigned int cost,
                           std::vector<std::string>& extra, unsigned int objectTypeId,
                           std::string& itemType, std::vector<std::string>& keywords,
                           std::string& longDesc, std::string& shortDesc,
                           std::vector<std::string>& wearFlags, int weight)
    : m_attribute(attribute),
      m_cost(cost),
      m_extra(extra),
      m_objectTypeId(objectTypeId),
      m_itemType(itemType),
      m_keywords(keywords),
      m_longDesc(longDesc),
      m_shortDesc(shortDesc),
      m_wearFlags(wearFlags) {}