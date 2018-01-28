#include "RoomEntity.h"

RoomEntity::RoomEntity() : m_desc(""){};
// Sample generic entity, assume properly formatted strings..
RoomEntity::RoomEntity(std::string desc, std::vector<DoorEntity> doors,
                       std::string extDesc, std::string name,
                       unsigned int roomId)
    : m_desc(desc),
      m_doors(doors),
      m_extDesc(extDesc),
      m_name(name),
      m_roomId(roomId) {}

std::string RoomEntity::getDesc() {
    m_desc = "dummy description";
    return m_desc;
}

unsigned int getDestRoomIdOf(std::string dir) { return 0; }

std::vector<std::string> getDirs() {
    std::vector<std::string> res;
    return res;
}

void reset() { return; }

std::string addEntity(const unsigned int entityToAdd) { return ""; }

std::string showEntitiesInRoom() { return ""; }

std::string removeEntity(const unsigned int entityToRemove) { return ""; }

unsigned int addPlayerToRoom(unsigned int playerId) { return 0; }

unsigned int removePlayerFromRoom(unsigned int playerId) { return 0; }

bool isAloneInRoom() { return false; }