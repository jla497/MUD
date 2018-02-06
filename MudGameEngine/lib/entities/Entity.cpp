#include <string>

#include "entities/Entity.h"

Entity::Entity() {
	m_entityId = UniqueId();
}

const UniqueId& Entity::getEntityId() const { return m_entityId; }
