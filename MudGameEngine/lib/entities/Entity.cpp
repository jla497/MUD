#include <string>

#include "entities/Entity.h"

Entity::Entity() {
	m_entityId = UniqueId();
}

UniqueId Entity::getEntityId() { return m_entityId; }
