#include <string>
#include <vector>

#include "ObjectEntity.h"

ObjectEntity::ObjectEntity(UniqueId& id, std::vector<std::string>& attributes,
                           unsigned int cost, std::vector<std::string>& descExtra,
                           std::vector<std::string>& keywordsExtra,
                           unsigned int objectTypeId, std::string& itemType,
                           std::vector<std::string>& keywords,
                           std::vector<std::string>& longDesc, std::string& shortDesc,
                           std::vector<std::string>& wearFlags, int weight)
    : Entity::Entity(id),
      m_attributes(attributes),
      m_cost(cost),
      m_objectTypeId(objectTypeId),
      m_itemType(itemType),
      m_keywords(keywords),
      m_longDesc(longDesc),
      m_shortDesc(shortDesc),
      m_wearFlags(wearFlags) {
   m_extra = {
      descExtra,
      keywordsExtra
   };
}