#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <boost/foreach.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <memory>
#include <unordered_map>

#include "entities/AreaEntity.h"
#include "entities/PlayerCharacter.h"
//#include "Room.h"
#include "gamemanager/LutBuilder.h"
#include "YamlParser.h"
#include "UniqueId.h"

namespace mudserver {
namespace gamemanager {

using namespace boost::bimaps;
typedef bimap<set_of<UniqueId>, list_of<roomId>> CharacterRoomLookupTable;
//typedef std::unordered_map<RoomID, Room> RoomLookupTable;
typedef std::map<roomId, RoomEntity*> RoomLookupTable;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

/**
 * The overarching idea of GameState is that it should
 *      - be owned by the GameManager
 *      - own all the information required to save/serialize a game
 *      - be the source of truth for all state relating to the world
 */
class GameState {

    CharacterRoomLookupTable characterRoomLookUp;
    RoomLookupTable roomLookUp;
    vector<AreaEntity*> areas;
    YamlParser parser;

public:

    GameState();

    void parseYamlFile(std::string string);
    void initRoomLUT();

    void addAreaFromParser();
    void addCharacterToLookUp(PlayerCharacter* character, RoomEntity* room);
    void addRoomToLUT(RoomEntity*);
    AreaEntity* getAreaFromParser();
    vector<AreaEntity*> getAreasVector();
    vector<UniqueId> getCharactersInRoom(RoomEntity* room);
    RoomEntity* getCharacterLocation(PlayerCharacter* character);
    RoomEntity* getRoomFromLUT(const roomId);
    void clearAreas();
    void clearCharacterRoomLUT();

    };

}  // namespace gamemanager
}  // namespace mudserver
#endif  // GAMESTATE_H
