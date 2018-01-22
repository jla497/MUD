#ifndef ROOM_ENTITY_H
#define ROOM_ENTITY_H

#include <sstream>
#include <unistd.h>
#include <memory>
#include <string>
#include <vector>
#include "Entity.h"

struct Door {
	std::string desc;	
	std::string dir; // didn't enum dir, could be arbitrary
	std::vector<std::string> keywords;
	unsigned int to; // Room this door leads to

	// https://stackoverflow.com/questions/15517991/search-a-vector-of-objects-by-object-attribute
	// use std::find_if instead
	// find_to(std::string dir) : dir_(dir) {}
	// bool operator()(Door& door) {return door.dir == dir_;}
// private:
// 	Door door;
};

class RoomEntity {
    // Room info from files
    unsigned int id;
    std::string desc;
    std::vector<Door> m_doors;
    std::string extDesc;
    std::string name;

    // Tentative organization structure of room contents
    std::vector<unsigned int> idPlayersInRoom;
    // ASSUME ids are unique for ALL entities, entities include npc, obj, equip, give
    // Room holds responsibiliy of item location, not item
    std::vector<unsigned int> idEntitiesInRoom; 
    
public:
    RoomEntity();
	RoomEntity(std::string desc);

	std::string getDesc();

	unsigned int getId();

	// Returns destinationID to room given dir command while in a room
	// Returns 0 if dir does not exist for room
	// (use find_to)
	unsigned int getDestRoomIdOf(std::string dir);

	// Returns list of doors available in room (e.g for showing options to player)
	std::vector<std::string> getDirs();
	
	// Reset room according to YML file
	// DOES NOT purge player from room, only affects non-player entities
	void reset(/*parsed YML data*/);

	// Returns success msg if inserts given entity into room succeeds
	// Given entity id
	std::string addEntity(const unsigned int entityToAdd);

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
