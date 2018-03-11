#include <algorithm>

#include "entities/RoomEntity.h"

RoomEntity::RoomEntity(const std::vector<std::string> &desc,
                       const std::vector<DoorEntity> &doors,
                       const std::vector<std::string> &descExt,
                       const std::vector<std::string> &keywordsExt,
                       const std::string &name, unsigned int roomId)
    : Entity::Entity(), m_desc(desc), m_doors(doors),
      m_name(name), m_extDesc{descExt, keywordsExt}, m_roomId(roomId) {}

unsigned int RoomEntity::getId() const { return m_roomId; }

std::string RoomEntity::getName() const { return m_name; }

std::vector<std::string> RoomEntity::getDesc() const { return m_desc; }

std::vector<std::string> RoomEntity::getExtendedDesc() const {
    return m_extDesc.desc;
}

std::vector<std::string> RoomEntity::getExtendedKeywords() const {
    return m_extDesc.keywords;
}

unsigned int RoomEntity::getDestRoomIdOf(const std::string &dir) const {
    auto door = std::find_if(std::begin(m_doors), std::end(m_doors),
                             [&](auto &d) { return d.getDir() == dir; });
    // error checking
    if (door == m_doors.end()) {
        // FIXME hardcoding error values
        return static_cast<unsigned int>(-1);
    }
    return door->getDestRoomId();
}

std::vector<std::string> RoomEntity::getDirs() const {
    std::vector<std::string> dirList;
    for (auto &door : m_doors) {
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

std::string RoomEntity::removeEntity(unsigned int entityToRemove) { return {}; }

void RoomEntity::equipObject(ObjectEntity &object) {
    m_objects[object.getObjectTypeId()] = object;
}
ObjectEntity RoomEntity::getObject(int id) {
    auto objectItr = m_objects.find(id);
    if (objectItr != m_objects.end()) {
        auto object = objectItr->second;
        m_objects.erase(objectItr);
        return object;
    } else {
        throw "no such object found";
    }
}

std::map<int, ObjectEntity> RoomEntity::getObjects() { return m_objects; };