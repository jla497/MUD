#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <boost/foreach.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <memory>
#include <unordered_map>

#include "Area.h"
#include "Player.h"
#include "Room.h"
#include "gamemanager/LutBuilder.h"
#include "YamlParser.h"

namespace mudserver {
namespace gamemanager {

using namespace boost::bimaps;
typedef bimap<set_of<CharacterID>, list_of<RoomID>> CharacterRoomLookupTable;
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

//    parser.loadYamlFile("detailed_mongoose.yml");
    vector<Area> areas;
//    std::map<roomId, RoomEntity*> roomLookUp = createLUT();

public:

    GameState();
    YamlParser parser;

    RoomEntity* getCharacterLocation(const Character& character);
    vector<CharacterID> getCharactersInRoom(const Room& room);

    void addRoomToLUT(RoomEntity*);
    RoomEntity* getRoomFromLUT(const RoomID);

    void addArea(const Area& area);
    vector<Area> getAreas();

    void addCharacterToLookUp(Character& character, RoomEntity* room);

    void clearAreas();
    void clearRoomLUT();
    void clearCharacterRoomLUT();

    void parseYamlFile(std::string string);
    RoomLookupTable initRoomLUT();

    };

}  // namespace gamemanager
}  // namespace mudserver
#endif  // GAMESTATE_H
