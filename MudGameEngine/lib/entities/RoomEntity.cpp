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

std::vector<std::string> RoomEntity::getDesc() { return m_desc; }

unsigned int getDestRoomIdOf(std::string& dir) { return 0; }

std::vector<std::string> getDirs() {
    // TODO: remove this dummy stuff
    std::vector<std::string> res;
    return res;
}

// void reset() { return; }

std::string addEntity(const unsigned int entityToAdd) { return ""; }

std::string getEntitiesInRoom() { return ""; }

std::string removeEntity(const unsigned int entityToRemove) { return ""; }
