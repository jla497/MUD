#include <iostream>

#include "gamemanager/GameState.h"
#include "logging.h"

namespace mudserver {
namespace gamemanager {

using std::make_unique;

void GameState::initFromYaml(std::string filename) {
    parseYamlFile(std::move(filename));
    addAreaFromParser();
    initRoomLUT();
    factory = std::unique_ptr<EntityFactory>(parser.makeFactory());
}

void GameState::parseYamlFile(std::string filename) {
    parser.loadYamlFile(std::move(filename));
}

void GameState::initRoomLUT() {
    for (auto& area : areas) {
        auto& rooms = area->getAllRooms();
        LutBuilder lutBuilder;
        roomLookUp = lutBuilder.createLUT(rooms);
    }
}


/**
 * Add Methods
 */

void GameState::addCharacterRoomRelationToLUT(UniqueId characterId,unsigned int roomId) {
    characterRoomLookUp.left[characterId] = roomId;
}

void GameState::addRoomToLUT(RoomEntity* room) {
    roomLookUp[room->getId()] = room;
}

void GameState::addCharacter(unique_ptr<PlayerCharacter> character) {
    auto id = character->getEntityId();
    characterLookUp[id] = std::move(character);
    //TODO: implement a configurable default spawn point
    //currently just takes the first room loaded
        auto roomLookupBegin = roomLookUp.begin();
    if (roomLookupBegin != roomLookUp.end()) {
        addCharacterRoomRelationToLUT(id, roomLookupBegin->second->getId());
    } else {
        auto logger = logging::getLogger("GameState::addCharacter");
        logger->error("No rooms found, character not added to room");
    }
}

void GameState::addAreaFromParser() {
    areas.push_back(std::move(parser.getArea()));
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
    auto roomid = characterRoomLookUp.left.find(character.getEntityId())->second;
    
    auto room = roomLookUp.find(roomid)->second;
    // std::cout<<"room's id: "<<room->getId()<<std::endl;
    return roomLookUp.find(roomid)->second;
}

vector<UniqueId> GameState::getCharactersInRoom(RoomEntity* room) {
    if (room == nullptr) {
        //return an empty vector
        return {};
    }
    vector<UniqueId> characters;
    for (auto& p : characterRoomLookUp.left ) {
        if (p.second == room->getId()) {
            characters.push_back(p.first);
        }
    }
    return characters;
}

AreaEntity* GameState::getAreaFromParser() {
    return parser.getArea().get();
}

deque<unique_ptr<AreaEntity>>& GameState::getAreas() {
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

EntityFactory& GameState::getFactory() {
    return *factory;
}

void GameState::doReset() {
    auto resets = parser.getAllResets();
    
    for(auto& reset: resets) {
        reset->execute(*this);
    }

}

}  // namespace gamemanager
}  // namespace mudserver
