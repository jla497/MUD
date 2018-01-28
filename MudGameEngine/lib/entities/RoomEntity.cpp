#include "RoomEntity.h"

RoomEntity::RoomEntity(): desc("") {};
// Sample generic entity, assume properly formatted strings..
RoomEntity::RoomEntity(std::string desc)
	: desc(desc) {
	id = rand();
}

std::string RoomEntity::getDesc() {
	desc = "dummy description";
	return desc;
}

unsigned int RoomEntity::getId() {
	return id;
}

unsigned int getDestRoomIdOf(std::string dir) {
	return 0; 
}

std::vector<std::string> getDirs() {
	std::vector<std::string> res;
	return res;
}

void reset() {
	return;
}

std::string addEntity(const unsigned int entityToAdd) {
	return "";
}

std::string showEntitiesInRoom() {
	return "";
}

std::string removeEntity(const unsigned int entityToRemove) {
	return "";
}

unsigned int addPlayerToRoom(unsigned int playerId) {
	return 0;
}

unsigned int removePlayerFromRoom(unsigned int playerId) {
	return 0;
}

bool isAloneInRoom() {
	return false;
}