#include <string>
#include <vector>

#include "AreaEntity.h"

AreaEntity::AreaEntity(UniqueId& id, std::string& name,
                       std::vector<unsigned int> rooms)
    : Entity::Entity(id), m_name(name), m_rooms(rooms) {}