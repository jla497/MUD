#ifndef ROOM_ENTITY_H
#define ROOM_ENTITY_H

#include "DoorEntity.h"
#include "Entity.h"

class RoomEntity {
   private:
    std::string m_desc;
    std::vector<DoorEntity> m_doors;
    std::string m_extDesc;
    std::string m_name;
    unsigned int m_roomId;

    // Tentative organization structure of room contents
    std::vector<unsigned int> m_idPlayersInRoom;
    // ASSUME ids are unique for ALL entities, entities include npc, obj, equip,
    // give
    // Room holds responsibiliy of item location, not item
    std::vector<unsigned int> m_idEntitiesInRoom;

   public:
    RoomEntity();
    RoomEntity(std::string desc, std::vector<DoorEntity> doors,
               std::string extDesc, std::string name, unsigned int roomId);

    std::string getDesc();

    // Returns destinationID to room given dir command while in a room
    // Returns 0 if dir does not exist for room
    // (use find_to)
    // Does not check whether that room exists yet
    unsigned int getDestRoomIdOf(std::string dir);

    // Returns list of doors available in room (e.g for showing options to
    // player)
    std::vector<std::string> getDirs();

    // Reset room according to YML file
    // DOES NOT purge player from room, only affects non-player entities
    void reset(/*parsed YML data*/);

    // Returns success msg if inserts given entity into room succeeds
    // Given entity id
    std::string addEntity(const unsigned int entityToAdd);

    // Return all entities in the room
    // Should it even be strings?
    std::string getEntitiesInRoom();

    // Returns success or failure msg if removes given entity into room succeeds
    // Given entity id
    std::string removeEntity(const unsigned int entityToRemove);

    // This function should be called when Player moves to a new room,
    // somehow need to ensure this is updated...
    // Player also keeps track of what room they are in
    unsigned int addPlayerToRoom(unsigned int playerId);

    // Would check if player is in this room and remove if true
    // Note that player can only be in one room at a time
    unsigned int removePlayerFromRoom(unsigned int playerId);

    // Returns true if player is alone in the room
    bool isAloneInRoom();
};

#endif
