#include <boost/format.hpp>
#include <iostream>
#include <memory>

#include "gamemanager/GameState.h"
#include "logging.h"

namespace mudserver {
namespace gamemanager {

std::size_t UniqueIdHash::operator()(UniqueId id) const {
    return std::hash<unsigned int>()(id.getId());
}

void GameState::initFromYaml(std::vector<std::string> areaFilenames,
                             std::vector<std::string> spellFilenames) {
    for (auto areaFilename : areaFilenames) {
        parseAreaYamlFile(std::move(areaFilename));
        addAreaFromParser();
    }
    initRoomLUT();

    for (auto spellFilename : spellFilenames) {
        parseSpellYamlFile(std::move(spellFilename));
        addSpellsFromParser();
    }

    factory = std::unique_ptr<EntityFactory>(areaParser.makeFactory());
    factory->init();
}

void GameState::parseAreaYamlFile(std::string filename) {
    areaParser.loadYamlFile(filename);
}

void GameState::initRoomLUT() {
    for (auto &area : areas) {
        auto &rooms = area.getAllRooms();
        LutBuilder lutBuilder;
        roomLookUp = lutBuilder.createLUT(rooms);
    }
}

void GameState::parseSpellYamlFile(std::string filename) {
    spellParser.loadYamlFile(std::move(filename));
}

/**
 * Add Methods
 */

void GameState::addCharacterRoomRelationToLUT(UniqueId characterId,
                                              unsigned int roomId) {
    characterRoomLookUp.left[characterId] = roomId;
}


void GameState::addRoomToLUT(const RoomEntity &room) {
    roomLookUp[room.getId()] = room;
}

void GameState::addCharacter(CharacterEntity &character) {
    auto id = character.getEntityId();
    characterLookUp[id] = std::move(character);
    // TODO: implement a configurable default spawn point
    // currently just takes the first room loaded
    auto roomLookupBegin = roomLookUp.begin();
    if (roomLookupBegin != roomLookUp.end()) {
        addCharacterRoomRelationToLUT(id, roomLookupBegin->second.getId());
    } else {
        auto logger = logging::getLogger("GameState::addCharacter");
        logger->error("No rooms found, character not added to room");
    }
}

void GameState::addCharacter(CharacterEntity &character, Id roomID) {
    auto id = character.getEntityId();
    characterLookUp[id] = std::move(character);
    // TODO: implement a configurable default spawn point
    // currently just takes the first room loaded
    auto roomIt = roomLookUp.find(roomID);
    if (roomIt != roomLookUp.end()) {
        addCharacterRoomRelationToLUT(id, roomIt->second.getId());
    } else {
        throw "couldn't add character to room";
    }
}

void GameState::addAreaFromParser() { areas.push_back(areaParser.getArea()); }

void GameState::addSpellsFromParser() { spells = spellParser.getAllSpells(); }
/**
 * Get Methods
 */
RoomEntity *GameState::getRoomFromLUT(const roomId id) {
    auto it = roomLookUp.find(id);
    return it != roomLookUp.end() ? &it->second : nullptr;
}

CharacterEntity *GameState::getCharacterFromLUT(UniqueId id) {
    auto it = characterLookUp.find(id);
    return it != characterLookUp.end() ? &it->second : nullptr;
}

RoomEntity *GameState::getCharacterLocation(const CharacterEntity &character) {
    auto it = characterRoomLookUp.left.find(character.getEntityId());
    if (it == characterRoomLookUp.left.end()) {
        return nullptr;
    }
    auto it2 = roomLookUp.find(it->second);
    return it2 != roomLookUp.end() ? &it2->second : nullptr;
}

std::vector<UniqueId> GameState::getCharactersInRoom(RoomEntity *room) {
    if (room == nullptr) {
        // return an empty vector
        return {};
    }
    std::vector<UniqueId> characters;
    characters.reserve(characterRoomLookUp.left.size());
    for (auto &p : characterRoomLookUp.left) {
        if (p.second == room->getId()) {
            characters.push_back(p.first);
        }
    }
    return characters;
}

AreaEntity GameState::getAreaFromParser() { return areaParser.getArea(); }

std::deque<AreaEntity> &GameState::getAreas() { return areas; }

std::vector<Spell> &GameState::getSpells() { return spells; }

/**
 * Clear Methods
 */
void GameState::removeCharacterByUniqueId(UniqueId characterId) {
    // TODO remove chara from these throw
    // characterRoomLookUp try characterRoomLookUp.left[characterId].erase()
    characterLookUp.erase(characterId);
}
void GameState::clearCharacterRoomLUT() { characterRoomLookUp.clear(); }

void GameState::clearAreas() { roomLookUp.clear(); }

EntityFactory &GameState::getFactory() { return *factory; }

void GameState::doReset() {
    auto resets = areaParser.getAllResets();
    ResetManager resetManager{resets};
    resetManager.applyResets(this);
}

Spell *GameState::getSpellByName(const std::string spellName) {
    auto foundSpell = std::find_if(spells.begin(), spells.end(), [spellName](Spell& tmp){
        return tmp.getName() == spellName;
    } );
}

void GameState::killCharacter(const CharacterEntity &character) {
    // remove from play
    // TODO: uncomment and integrate once branches have been merged
    removeCharacterByUniqueId(character.getEntityId());

    // if the character is controlled by a player notify them
}

} // namespace gamemanager
} // namespace mudserver
