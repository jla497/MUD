#include <string>
#include <vector>
#include <deque>

#include "entities/AreaEntity.h"

AreaEntity::AreaEntity(std::string& name,
                       std::deque<std::unique_ptr<RoomEntity>> rooms)
    : Entity::Entity(), m_name(name), m_rooms(std::move(rooms)) {}

std::deque<std::unique_ptr<RoomEntity>>& AreaEntity::getAllRooms() {
 	return m_rooms;
 }
std::string AreaEntity::getName() {
	return m_name;
}
