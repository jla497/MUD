#include <algorithm>

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

std::vector<std::string> RoomEntity::getDesc() const { 
  return m_desc; 
}

// TODO, should be able to make this method const...
unsigned int RoomEntity::getDestRoomIdOf(std::string& dir) { 
  std::vector<DoorEntity>::iterator door = std::find_if(std::begin(m_doors), std::end(m_doors), 
    [&] (DoorEntity const& d) { 
      return d.getDir() == dir; 
    });  
  return door->getDestRoomId();
}

std::vector<std::string> RoomEntity::getDirs() const {    
    std::vector<std::string> dirList;
    for (const auto& door : m_doors)
    {  
        dirList.push_back(door.getDir());
    }
    return dirList;
}

// void reset() { return; }

std::string RoomEntity::addEntity(const unsigned int entityToAdd) { 
  // TODO error checking?
  return ""; 
}

std::vector<unsigned int> RoomEntity::getEntitiesInRoom() const {
  return m_idEntitiesInRoom; 
}

std::string RoomEntity::removeEntity(const unsigned int entityToRemove) { return ""; }
