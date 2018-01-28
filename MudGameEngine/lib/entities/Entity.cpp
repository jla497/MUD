#include <string>

#include "Entity.h"

Entity::Entity() {
	//generate entityId
    m_entityId = nextUniqueId++;
}

unsigned int Entity::getEntityId() {
	return m_entityId;
}

// std::string Entity::getDesc() {
// 	return m_desc;
// }