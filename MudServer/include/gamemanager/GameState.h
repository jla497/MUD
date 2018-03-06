#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <boost/bimap.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/foreach.hpp>
#include <deque>
#include <memory>
#include <unordered_map>

#include "UniqueId.h"
#include "UniqueId.h"
#include "YamlParser.h"
#include "YamlParser.h"
#include "entities/AreaEntity.h"
#include "entities/CharacterEntity.h"
#include "entities/DoorEntity.h"
#include "gamemanager/LutBuilder.h"
#include "reset/Reset.h"
#include "reset/ResetManager.h"

class Reset;
namespace mudserver {
namespace gamemanager {

using namespace boost::bimaps;

struct UniqueIdHash {
  public:
    std::size_t operator()(UniqueId id) const;
};

/**
 * The overarching idea of GameState is that it should
 *      - be owned by the GameManager
 *      - own all the information required to save/serialize a game
 *      - be the source of truth for all state relating to the world
 */
class GameState {
  private:
    bimap<set_of<UniqueId>, list_of<roomId>> characterRoomLookUp;
    std::unordered_map<roomId, RoomEntity> roomLookUp;
    std::unordered_map<UniqueId, CharacterEntity, UniqueIdHash> characterLookUp;
    std::deque<AreaEntity> areas;
    YamlParser parser;
    AreaEntity area;
    std::unique_ptr<EntityFactory> factory;

  public:
    void initFromYaml(std::string filename);
    void parseYamlFile(std::string string);
    void initRoomLUT();
    void addAreaFromParser();

    void addCharacter(CharacterEntity &character);
    void addCharacterRoomRelationToLUT(UniqueId characterId,
                                       unsigned int roomId);
    void addRoomToLUT(const RoomEntity &room);
    AreaEntity getAreaFromParser();
    std::deque<AreaEntity> &getAreas();
    std::vector<UniqueId> getCharactersInRoom(RoomEntity *room);
    CharacterEntity *getCharacterFromLUT(UniqueId id);
    void addCharacter(CharacterEntity &character, Id roomID);
    RoomEntity *getCharacterLocation(const CharacterEntity &character);
    RoomEntity *getRoomFromLUT(const roomId);
    void clearAreas();
    void clearCharacterRoomLUT();
    EntityFactory &getFactory();
    void doReset();

    /**
     * Swaps two the ID of two characters in characterLookUp map
     * @param casterId UniqueId of character
     * @param targetId UniqueId of character
     */
    void swapCharacters(UniqueId casterId, UniqueId targetId);
};

} // namespace gamemanager
} // namespace mudserver
#endif // GAMESTATE_H
