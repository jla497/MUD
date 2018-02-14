#include <algorithm>

#include "entities/RoomEntity.h"

RoomEntity::RoomEntity(const std::vector<std::string>& desc,
                       const std::vector<DoorEntity> &doors,
                       const std::vector<std::string>& descExt,
                       const std::vector<std::string>& keywordsExt, const std::string& name,
                       unsigned int roomId)
    : Entity::Entity(),
      m_desc(desc),
      m_doors(),
      m_name(name),
      m_extDesc{descExt, keywordsExt},
    m_roomId(roomId)
{}

unsigned int RoomEntity::getId() const {
  return m_roomId;
}

std::string RoomEntity::getName() const {
  return m_name;
}

std::vector<std::string> RoomEntity::getDesc() const {
  return m_desc;
}

std::vector<std::string> RoomEntity::getExtendedDesc() const {
  return m_extDesc.desc;
}

std::vector<std::string> RoomEntity::getExtendedKeywords() const {
  return m_extDesc.keywords;
}

// TODO, should be able to make this method const...
unsigned int RoomEntity::getDestRoomIdOf(std::string& dir) { 
  auto door = std::find_if(std::begin(m_doors), std::end(m_doors),
         [&] (auto &d) {
             return d.getDir() == dir;
         });
  //error checking
  if(door == m_doors.end()) {
      //FIXME hardcoding error values
    return static_cast<unsigned int>(-1);
  }
  return door->getDestRoomId();
}

std::vector<std::string> RoomEntity::getDirs() const {    
    std::vector<std::string> dirList;
    for (auto& door : m_doors)
    {  
        dirList.push_back(door.getDir());
    }
    return dirList;
}

std::string RoomEntity::addEntity(unsigned int entityToAdd) {
  // TODO error checking?
  return {};
}

std::vector<unsigned int> RoomEntity::getEntitiesInRoom() const {
  return m_idEntitiesInRoom; 
}

std::string RoomEntity::removeEntity(unsigned int entityToRemove) {
    return {};
}
