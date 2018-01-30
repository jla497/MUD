#include <iostream>

#include "gamemanager/GameState.h"

namespace mudserver {
namespace gamemanager {

using std::make_unique;

GameState::GameState() {}

Room& GameState::getCharacterLocation(const Character& character) {
    // TODO: implement getCharacterLocation stub
    return *(new Room());
}

}  // namespace gamemanager
}  // namespace mudserver
