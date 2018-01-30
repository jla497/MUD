#include <string>

#include "Entity.h"

Entity::Entity(UniqueId& id) : m_entityId(id) {}

UniqueId Entity::getEntityId() { return m_entityId; }
