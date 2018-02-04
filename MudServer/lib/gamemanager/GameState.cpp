#include <iostream>

#include "gamemanager/GameState.h"

namespace mudserver {
namespace gamemanager {

using std::make_unique;

GameState::GameState() {

}


void GameState::parseYamlFile(std::string filename) {
    parser.loadYamlFile(filename);
}

//RoomLookupTable GameState::initRoomLUT() {
//    auto area = parser.getArea();
//    auto& rooms = area->getAllRooms();
//    LutBuilder lutBuilder;
//    return lutBuilder.createLUT(rooms);
//}

/**
 * Add Methods
 */
void GameState::addCharacterToLookUp(Character& character, RoomEntity* room) {
    characterRoomLookUp.left[character.getID()] = room->getId();
}

void GameState::addRoomToLUT(RoomEntity* room) {
    roomLookUp[room->getId()] = room;
}

void GameState::addArea(const Area& area) {
    areas.push_back(area);
}


/**
 * Get Methods
 */
RoomEntity* GameState::getRoomFromLUT(const RoomID id) {
    return roomLookUp.find(id)->second;
}

RoomEntity* GameState::getCharacterLocation(const Character& character) {
    auto id = characterRoomLookUp.left.find(character.getID())->second;
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

//void GameState::clearRoomLUT() {
//    roomLookUp.clear();
//}

void GameState::clearAreas() {
    roomLookUp.clear();
}


}  // namespace gamemanager
}  // namespace mudserver
