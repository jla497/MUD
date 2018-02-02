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
    return characters;
}

Room& GameState::getRoom(const RoomID id) {
    return roomLookUp.find(id)->second;
}

//void GameState::addRoom(const RoomID id) {
//    roomLookUp[id] = Room(id);
//}


}  // namespace gamemanager
}  // namespace mudserver
