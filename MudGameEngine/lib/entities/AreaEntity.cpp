#include <string>
#include <vector>
#include <deque>

#include "entities/AreaEntity.h"

AreaEntity::AreaEntity(const std::string& name,
                       std::deque<RoomEntity> rooms)
    : Entity::Entity(), m_name(name), m_rooms(std::move(rooms)) {}

std::deque<RoomEntity>& AreaEntity::getAllRooms() {
 	return m_rooms;
 }
std::string AreaEntity::getName() {
	return m_name;
}
