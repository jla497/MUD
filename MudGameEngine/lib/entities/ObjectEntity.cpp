#include <string>
#include <utility>
#include <vector>

#include "entities/ObjectEntity.h"

ObjectEntity::ObjectEntity(
    std::vector<std::string> attributes, unsigned int cost,
    std::vector<std::string> descExtra, std::vector<std::string> keywordsExtra,
    unsigned int objectTypeId, std::string itemType,
    std::vector<std::string> keywords, std::vector<std::string> longDesc,
    std::string shortDesc, std::vector<std::string> wearFlags, int weight)
    : Entity::Entity(), m_attributes(std::move(attributes)), m_cost(cost),
      m_objectTypeId(objectTypeId), m_itemType(std::move(itemType)),
      m_keywords(std::move(keywords)), m_longDesc(std::move(longDesc)),
      m_shortDesc(std::move(shortDesc)), m_wearFlags(std::move(wearFlags)) {
    m_extra = {std::move(keywordsExtra), std::move(descExtra)};
}

// Need to change this to somehow give a different one
// each time
std::vector<std::string> ObjectEntity::getAttributes() const {
    return m_attributes;
}

unsigned int ObjectEntity::getCost() const { return m_cost; }

unsigned int ObjectEntity::getObjectTypeId() const { return m_objectTypeId; }

std::string ObjectEntity::getItemType() const { return m_itemType; }

std::vector<std::string> ObjectEntity::getKeywords() const {
    return m_keywords;
}

std::vector<std::string> ObjectEntity::getLongDesc() const {
    return m_longDesc;
}

std::string ObjectEntity::getShortDesc() const { return m_shortDesc; }

std::vector<std::string> ObjectEntity::getWearFlags() const {
    return m_wearFlags;
}

std::vector<std::string> ObjectEntity::getExtraKeyword() const {
    return m_extra.keywords;
}

std::vector<std::string> ObjectEntity::getExtraDesc() const {
    return m_extra.desc;
}