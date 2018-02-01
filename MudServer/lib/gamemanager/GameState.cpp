#include <iostream>

#include "gamemanager/GameState.h"

namespace mudserver {
namespace gamemanager {

using std::make_unique;

GameState::GameState() {

}

Room& GameState::getCharacterLocation(const Character& character) {
    // TODO: implement getCharacterLocation stub
    return *(new Room());
}

Room& GameState::getRoomFromCharacter(const Character& character) {
    RoomID id = characterRoomLookUp.left.at(character.getID());
    return roomLookUp.at(id);
}

vector<Character> GameState::getCharactersFromRoom(const Room& room) {
    vector<Character> characters;
    return characters;
}

Room& GameState::getRoomFromID(const RoomID id) {
    return roomLookUp.find(id)->second;
}


}  // namespace gamemanager
}  // namespace mudserver
