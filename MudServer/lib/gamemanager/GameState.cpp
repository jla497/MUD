#include <iostream>

#include "gamemanager/GameState.h"

namespace mudserver {
namespace gamemanager {

using std::make_unique;

GameState::GameState() {

}

Room& GameState::getCharacterLocation(const Character& character) {
    RoomID id = characterRoomLookUp.left.at(character.getID());
    return roomLookUp.at(id);
}

vector<Character> GameState::getCharactersInRoom(const Room& room) {
    vector<Character> characters;
    for(auto character : characterRoomLookUp.left) {
        if (character->second == room.getID()) {
            characters.push_back(character->first);
        }
    }
    return characters;
}

Room& GameState::getRoom(const RoomID id) {
    return roomLookUp.find(id)->second;
}

void GameState::addArea(const Area& area) {
    areas.push_back(area);
}

void GameState::updateCharacterLocation(Character& character, Room& room) {
    characterRoomLookUp.left[character.getID()] = room.getID();
}

}  // namespace gamemanager
}  // namespace mudserver
