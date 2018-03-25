
#include <algorithm>
#include <memory>

#include <boost/optional.hpp>

#include "entities/RoomEntity.h"
// REMOVE 
#include "entities/ObjectEntity.h"
//

RoomEntity::RoomEntity(const std::vector<std::string> &desc,
                       const std::vector<DoorEntity> &doors,
                       const std::vector<std::string> &descExt,
                       const std::vector<std::string> &keywordsExt,
                       const std::string &name, unsigned int roomId)
    : Entity::Entity(), m_desc(desc), m_doors(doors),
      m_name(name), m_extDesc{descExt, keywordsExt}, m_roomId(roomId) {

    // !!! REMOVE: For testing only
    ObjectEntity testObject{{"attribute"}, 2, {}, {}, 3, "useless type", {}, {}, "a uesless obj", {}, 5};
    addObject(testObject);
}

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
    (void)entityToAdd;
    // TODO error checking?
    return {};
}

std::vector<unsigned int> RoomEntity::getEntitiesInRoom() const {
    return m_idEntitiesInRoom;
}

std::string RoomEntity::removeEntity(unsigned int entityToRemove) {
    (void)entityToRemove;
    return {};
}

void RoomEntity::addObject(ObjectEntity &object) {
    m_objects[object.getObjectTypeId()] = object;
}

void RoomEntity::removeObject(boost::optional<ObjectEntity> &object) {
    std::map<int, ObjectEntity>::iterator it;
    it = m_objects.find(object->getObjectTypeId());
    m_objects.erase(it);
}

boost::optional<ObjectEntity> RoomEntity::takeObject(int id) {
    auto it = m_objects.find(id);
    if (it == m_objects.end()) {
        return {};
    }
    boost::optional<ObjectEntity> object{std::move(it->second)};
    m_objects.erase(it);
    return object;
}

boost::optional<ObjectEntity> RoomEntity::takeObjectByName(const std::string& objName) {
    for (auto const& obj : m_objects) {
        // compare object to name arg
        if (obj.second.getShortDesc() == objName) {
            return obj.second;
        }
    }
    return boost::none;
}

std::map<int, ObjectEntity> RoomEntity::getObjects() { return m_objects; };