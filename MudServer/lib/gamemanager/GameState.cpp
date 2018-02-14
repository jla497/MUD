#include <iostream>
#include <memory>

#include "gamemanager/GameState.h"
#include "logging.h"

namespace mudserver {
namespace gamemanager {

std::size_t UniqueIdHash::operator()(UniqueId id) const {
    return std::hash<unsigned int>()(id.getId());
}

void GameState::initFromYaml(std::string filename) {
    parseYamlFile(std::move(filename));
    addAreaFromParser();
    initRoomLUT();
}

void GameState::parseYamlFile(std::string filename) {
    parser.loadYamlFile(std::move(filename));
}

void GameState::initRoomLUT() {
    for (auto& area : areas) {
        auto& rooms = area.getAllRooms();
        LutBuilder lutBuilder;
        roomLookUp = lutBuilder.createLUT(rooms);
    }
}

/**
 * Add Methods
 */

void GameState::addCharacterRoomRelationToLUT(UniqueId characterId, unsigned int roomId) {
    characterRoomLookUp.left[characterId] = roomId;
}

void GameState::addRoomToLUT(const RoomEntity &room) {
    roomLookUp[room.getId()] = room;
}

void GameState::addCharacter(PlayerCharacter &character) {
    auto id = character.getEntityId();
    characterLookUp[id] = std::move(character);
    //TODO: implement a configurable default spawn point
    //currently just takes the first room loaded
    auto roomLookupBegin = roomLookUp.begin();
    if (roomLookupBegin != roomLookUp.end()) {
        addCharacterRoomRelationToLUT(id, roomLookupBegin->second.getId());
    } else {
        auto logger = logging::getLogger("GameState::addCharacter");
        logger->error("No rooms found, character not added to room");
    }
}

void GameState::addAreaFromParser() {
    areas.push_back(parser.getArea());
}


/**
 * Get Methods
 */
RoomEntity* GameState::getRoomFromLUT(const roomId id) {
    auto it = roomLookUp.find(id);
    return it != roomLookUp.end() ? &it->second : nullptr;
}

PlayerCharacter* GameState::getCharacterFromLUT(UniqueId id) {
    auto it = characterLookUp.find(id);
    return it != characterLookUp.end() ? &it->second : nullptr;
}

RoomEntity* GameState::getCharacterLocation(const PlayerCharacter& character) {
    auto it = characterRoomLookUp.left.find(character.getEntityId());
    if (it == characterRoomLookUp.left.end()) {
        return nullptr;
    }
    auto it2 = roomLookUp.find(it->second);
    return it2 != roomLookUp.end() ? &it2->second : nullptr;
}

std::vector<UniqueId> GameState::getCharactersInRoom(RoomEntity* room) {
    if (room == nullptr) {
        //return an empty vector
        return {};
    }
    std::vector<UniqueId> characters;
    characters.reserve(characterRoomLookUp.left.size());
    for (auto& p : characterRoomLookUp.left ) {
        if (p.second == room->getId()) {
            characters.push_back(p.first);
        }
    }
    return characters;
}

AreaEntity GameState::getAreaFromParser() {
    return parser.getArea();
}

std::deque<AreaEntity>& GameState::getAreas() {
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
