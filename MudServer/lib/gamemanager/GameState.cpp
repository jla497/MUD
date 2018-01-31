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

Room& GameState::getRoomFromCharacterId(const Character& character) {
//    return characterRoomLookUp.right.at(character);
    return *(new Room());
}

Character& GameState::getCharacterFromRoomId(const Room& room) {
    return *(new Character());
}

Room& GameState::getRoomFromId(const RoomId) {
    return *(new Room());
}


}  // namespace gamemanager
}  // namespace mudserver
