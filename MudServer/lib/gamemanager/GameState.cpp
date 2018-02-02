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

vector<CharacterID> GameState::getCharactersInRoom(const Room& room) {
    vector<CharacterID> characters;

    BOOST_FOREACH(CharacterRoomLookupTable::left_const_reference p, characterRoomLookUp.left ) {
        if (p.second == room.getID()) {
            characters.push_back(p.first);
        }
    }

//    for( auto i : characterRoomLookUp.left)
//    {
//        if (i.second == room.getID())
//            characters.push_back(i.first);
//    }

//    for(auto id : characterRoomLookUp.left) {
//        if (characterRoomLookUp.left.at(id) == room.getID()) {
//            characters.push_back(characterRoomLookUp.right.at(id));
//        }
//    }
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
