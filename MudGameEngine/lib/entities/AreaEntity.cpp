#include <string>
#include <vector>

#include "entities/AreaEntity.h"

AreaEntity::AreaEntity(std::string& name,
                       std::vector<unsigned int> rooms)
    : Entity::Entity(), m_name(name), m_rooms(rooms) {}