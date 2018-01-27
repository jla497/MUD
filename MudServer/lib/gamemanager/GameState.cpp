#include <iostream>

#include "gamemanager/GameState.h"

namespace mudserver {
namespace gamemanager {

using std::make_unique;
    
GameState::GameState() :
    players{unordered_map<PlayerID, unique_ptr<Player>>()}
    { }

GameState::~GameState()
{

}

Player* GameState::getPlayerByID(const PlayerID id) {
    return new Player{42, "foo", "bar"};
    //return players[id].get();
}

Room& GameState::getCharacterLocation(const Character& character) {
    //TODO: implement getCharacterLocation stub
    return *(new Room());
}

}   // namespace mudserver
}   // namespace gamemanager
