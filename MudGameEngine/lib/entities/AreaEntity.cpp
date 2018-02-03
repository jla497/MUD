#include <string>
#include <vector>

#include "AreaEntity.h"

AreaEntity::AreaEntity(std::string& name,
                       std::vector<std::unique_ptr<RoomEntity>> rooms)
    : Entity::Entity(), m_name(name), m_rooms(std::move(rooms)) {}

 std::vector<std::unique_ptr<RoomEntity>>& AreaEntity::getAllRooms() {
 	return m_rooms;
 }