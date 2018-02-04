#include <string>
#include <vector>

#include "entities/AreaEntity.h"

AreaEntity::AreaEntity(std::string& name,
                       std::vector<std::unique_ptr<RoomEntity>> rooms)
    : Entity::Entity(), m_name(name), m_rooms(std::move(rooms)) {}

std::string AreaEntity::getName() {
	return m_name;
}