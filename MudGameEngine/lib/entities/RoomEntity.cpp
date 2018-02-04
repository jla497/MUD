#include "entities/RoomEntity.h"

RoomEntity::RoomEntity(std::vector<std::string>& desc,
                       std::vector<DoorEntity> doors,
                       std::vector<std::string>& descExt,
                       std::vector<std::string>& keywordsExt, std::string& name,
                       unsigned int roomId)
    : Entity::Entity(),
      m_desc(desc),
      m_doors(std::move(doors)),
      m_name(name),
      m_roomId(roomId) {
      m_extDesc = {descExt, keywordsExt};
}

std::vector<std::string> RoomEntity::getDesc() const { return m_desc; }

unsigned int RoomEntity::getDestRoomIdOf(std::string& dir) const { return 0; }

std::vector<std::string> RoomEntity::getDirs() const {
    // TODO: remove this dummy stuff
    std::vector<std::string> res;
    return res;
}

// void reset() { return; }

std::string RoomEntity::addEntity(const unsigned int entityToAdd) { return ""; }

std::string RoomEntity::getEntitiesInRoom() const { return ""; }

std::string RoomEntity::removeEntity(const unsigned int entityToRemove) { return ""; }
