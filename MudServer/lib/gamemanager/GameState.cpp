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

// void GameState::initRoomLUT() {
//     auto area = parser.getArea(); //this is a variable on stack. WIll get deleted after function ends
//     auto& rooms = area->getAllRooms();
//     LutBuilder lutBuilder;
//     roomLookUp = lutBuilder.createLUT(rooms);

//     printLut("all rooms listed in roomLookUp initRoomLUT: ");
// }

void GameState::initRoomLUT() {
    area = parser.getArea(); //this is a variable on stack. WIll get deleted after function ends
    auto& rooms = area->getAllRooms();
    LutBuilder lutBuilder;
    roomLookUp = lutBuilder.createLUT(rooms);

    printLut("all rooms listed in roomLookUp initRoomLUT: ");
}

void GameState::printLut(std::string where) {
    std::cout<<where<<std::endl;
    for( auto it = roomLookUp.begin(); it!= roomLookUp.end(); ++it) {
        std::cout<<"room key: "<<it->first<<std::endl;
        std::cout<<"room's actual id: "<<it->second->getId()<<std::endl;
        std::cout<<"room short: "<<it->second->getName()<<std::endl;
        if(it->first != it->second->getId()) {
            throw ("room key and id changed!");
        }
    }
}

/**
 * Add Methods
 */
void GameState::addCharacterRoomRelationToLUT(PlayerCharacter* character,
                                              RoomEntity* room) {
    std::cout<<"added new character: "<<character->getEntityId()<<std::endl;

    std::cout<<"char supposed to be placed in room: "<<room->getId()<<std::endl;
    characterRoomLookUp.left[character->getEntityId()] = room->getId();
    std::cout<<"char place in room: "<<characterRoomLookUp.left[character->getEntityId()]<<std::endl;

    printLut("all rooms listed in roomLookUp after adding character: ");
}

void GameState::addRoomToLUT(RoomEntity* room) {
    roomLookUp[room->getId()] = room;
}

void GameState::addCharacter(unique_ptr<PlayerCharacter> character) {
    auto id = character->getEntityId();
    characterLookUp[id] = std::move(character);
    //TODO: implement a configurable default spawn point
    //currently just takes the first room loaded
    printLut("all rooms listed in roomLookUp before adding char: ");

    addCharacterRoomRelationToLUT(characterLookUp[id].get(),
                                  roomLookUp.begin()->second);
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
    return characterLookUp.find(id)->second.get();
}

RoomEntity* GameState::getCharacterLocation(PlayerCharacter* character) {
    auto id = characterRoomLookUp.left.find(character->getEntityId())->second;
    return roomLookUp.find(id)->second;
}

RoomEntity* GameState::getCharacterLocation(PlayerCharacter& character) {
    std::cout<<"character id: "<<character.getEntityId().getId()<<std::endl;
    auto roomid = characterRoomLookUp.left.find(character.getEntityId())->second;
    std::cout<<"characterroom id: "<<roomid<<std::endl;
    
    printLut("all rooms listed in roomLookUp for getCharacterLocation: ");

    auto room = roomLookUp.find(roomid)->second;
    // std::cout<<"room's id: "<<room->getId()<<std::endl;
    return roomLookUp.find(roomid)->second;
}

vector<UniqueId> GameState::getCharactersInRoom(RoomEntity* room) {
    vector<UniqueId> characters;
    //TODO: can we use native foreach loop here?
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
