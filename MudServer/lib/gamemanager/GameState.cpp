#include <iostream>

#include "gamemanager/GameState.h"

namespace mudserver {
namespace gamemanager {

using std::make_unique;

GameState::GameState() {

}

/**
 * Add Methods
 */
void GameState::addCharacterToLookUp(Character& character, Room& room) {
    characterRoomLookUp.left[character.getID()] = room.getID();
}

void GameState::addRoomToLUT(const Room& room) {
    roomLookUp[room.getID()] = room;
}

void GameState::addArea(const Area& area) {
    areas.push_back(area);
}


/**
 * Get Methods
 */
Room& GameState::getRoomFromLUT(const RoomID id) {
    return roomLookUp.find(id)->second;
}

Room& GameState::getCharacterLocation(const Character& character) {
    RoomID id = characterRoomLookUp.left.find(character.getID())->second;
    return roomLookUp.find(id)->second;
}

vector<CharacterID> GameState::getCharactersInRoom(const Room& room) {
    vector<CharacterID> characters;
    BOOST_FOREACH(CharacterRoomLookupTable::left_const_reference p, characterRoomLookUp.left ) {
        if (p.second == room.getID()) {
            characters.push_back(p.first);
        }
    }
    return characters;
}

vector<Area> GameState::getAreas() {
    return areas;
}


    /**
 * Clear Methods
 */
void GameState::clearCharacterRoomLUT() {
    characterRoomLookUp.clear();
}

void GameState::clearRoomLUT() {
    roomLookUp.clear();
}

void GameState::clearAreas() {
    roomLookUp.clear();
}


}  // namespace gamemanager
}  // namespace mudserver
