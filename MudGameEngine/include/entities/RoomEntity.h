
#ifndef ROOM_ENTITY_H
#define ROOM_ENTITY_H

#include <map>

#include <boost/optional.hpp>

#include "DoorEntity.h"
#include "Entity.h"
#include "ObjectEntity.h"

struct ExtendedDesc {
    std::vector<std::string> desc;
    std::vector<std::string> keywords;
};

class RoomEntity : public Entity {
  private:
    std::vector<std::string> m_desc;
    std::vector<DoorEntity> m_doors;
    std::map<int, ObjectEntity> m_objects;
    std::string m_name;
    ExtendedDesc m_extDesc;
    unsigned int m_roomId = NO_ROOM_ID;

    /*
     * ASSUME ids are unique for ALL entities, entities include npc, obj, equip,
     * Room holds responsibility of item location, not item object itself
     * It is just a vector for look up
     */
    std::vector<unsigned int> m_idEntitiesInRoom;

  public:
    constexpr static auto NO_ROOM_ID = static_cast<unsigned int>(-1);

    RoomEntity() = default;

    RoomEntity(const std::vector<std::string> &desc,
               const std::vector<DoorEntity> &doors,
               const std::vector<std::string> &descExt,
               const std::vector<std::string> &keywordsExt,
               const std::string &name, unsigned int roomId);

    unsigned int getId() const;

    std::string getName() const;

    std::vector<std::string> getDesc() const;

    std::vector<std::string> getExtendedDesc() const;

    std::vector<std::string> getExtendedKeywords() const;

    /**
     * Returns destinationID to room given dir command while in a room
     * Returns 0 if dir does not exist for room
     * (use find_to)
     * Does not check whether that room exists yet
     */
    unsigned int getDestRoomIdOf(const std::string &dir) const;

    /**
     * Returns list of doors available in room (e.g for showing options to
     * player)
     */
    std::vector<std::string> getDirs() const;

    // Reset room according to YML file
    // DOES NOT purge player from room, only affects non-player entities
    // TODO: Not sure how resets are handled right now
    // void reset(/*parsed YML data*/);

    /*
     * Returns success msg if inserts given entity into room succeeds
     * Given entity id
     */
    std::string addEntity(unsigned int entityToAdd);

    /**
     *Return all entities in the room
     */
    std::vector<unsigned int> getEntitiesInRoom() const;

    /**
     *Returns success or failure msg if removes given entity into room succeeds
     * Given entity id
     */
    std::string removeEntity(unsigned int entityToRemove);
    void addObject(ObjectEntity &object);
    void removeObject(boost::optional<ObjectEntity> &object);
    void removeObject(UniqueId objectToRmvId);
    boost::optional<ObjectEntity> takeObject(int id);
    boost::optional<ObjectEntity> takeObjectByName(const std::string &objName);
    std::map<int, ObjectEntity> getObjects();
};

#endif
