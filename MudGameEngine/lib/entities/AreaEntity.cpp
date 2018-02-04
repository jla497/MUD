#include <string>
#include <vector>

#include "entities/AreaEntity.h"

AreaEntity::AreaEntity(std::string& name,
                       std::vector<unsigned int> rooms)
    : Entity::Entity(), m_name(name), m_rooms(rooms) {}

std::string AreaEntity::getName() const {
	return m_name;
}

std::vector<unsigned int> AreaEntity::getRooms() const {
	return m_rooms;
}