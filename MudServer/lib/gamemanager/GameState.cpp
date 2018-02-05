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

void GameState::initRoomLUT() {
    auto area = parser.getArea();
    auto& rooms = area->getAllRooms();
    LutBuilder lutBuilder;
    roomLookUp = lutBuilder.createLUT(rooms);
}

/**
 * Add Methods
 */
void GameState::addCharacterRoomRelationToLUT(PlayerCharacter* character, RoomEntity* room) {
    characterRoomLookUp.left[character->getEntityId()] = room->getId();
}

void GameState::addRoomToLUT(RoomEntity* room) {
    roomLookUp[room->getId()] = room;
}

void GameState::addCharacterToLUT(PlayerCharacter* character) {
    characterLookUp[character->getEntityId()] = character;
}

void GameState::addAreaFromParser() {
    areas.push_back(parser.getArea().get());
}


/**
 * Get Methods
 */
RoomEntity* GameState::getRoomFromLUT(const roomId id) {
    return roomLookUp.find(id)->second;
}

PlayerCharacter* GameState::getCharacterFromLUT(UniqueId id) {
//    unsigned int uid = std::stoul(id, nullptr, 0);
    return characterLookUp.find(id)->second;

}

RoomEntity* GameState::getCharacterLocation(PlayerCharacter* character) {
    auto id = characterRoomLookUp.left.find(character->getEntityId())->second;
    return roomLookUp.find(id)->second;
}

vector<UniqueId> GameState::getCharactersInRoom(RoomEntity* room) {
    vector<UniqueId> characters;
    BOOST_FOREACH(CharacterRoomLookupTable::left_const_reference p, characterRoomLookUp.left ) {
        if (p.second == room->getId()) {
            characters.push_back(p.first);
        }
    }
    return characters;
}

AreaEntity* GameState::getAreaFromParser() {
    return parser.getArea().get();
}

vector<AreaEntity*> GameState::getAreasVector() {
    return areas;
}


/**
 * Clear Methods
 */
void GameState::clearCharacterRoomLUT() {
    characterRoomLookUp.clear();
}

void GameState::clearAreas() {
    roomLookUp.clear();
}


}  // namespace gamemanager
}  // namespace mudserver
