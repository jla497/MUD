#ifndef ROOM_ENTITY_H
#define ROOM_ENTITY_H

#include "DoorEntity.h"
#include "Entity.h"

struct ExtendedDesc {
    std::vector<std::string> desc;
    std::vector<std::string> keywords;
};

class RoomEntity : public Entity {
private:
    std::vector<std::string> m_desc;
    std::vector<std::unique_ptr<DoorEntity>> m_doors;
    ExtendedDesc m_extDesc;
    std::string m_name;
    unsigned int m_roomId;

    /*
     * ASSUME ids are unique for ALL entities, entities include npc, obj, equip,
     * Room holds responsibility of item location, not item object itself
     * It is just a vector for look up
     */
    std::vector<unsigned int> m_idEntitiesInRoom;

public:
    RoomEntity(std::vector<std::string>& desc,
               std::vector<std::unique_ptr<DoorEntity>> doors,
               std::vector<std::string>& descExt,
               std::vector<std::string>& keywordsExt, std::string& name,
               unsigned int roomId);

    unsigned int getId();

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
    unsigned int getDestRoomIdOf(std::string& dir);

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
    std::string addEntity(const unsigned int entityToAdd);

    /**
     *Return all entities in the room
     */
    std::vector<unsigned int> getEntitiesInRoom() const;

    /**
     *Returns success or failure msg if removes given entity into room succeeds
     * Given entity id
     */
    std::string removeEntity(const unsigned int entityToRemove);
};

#endif
