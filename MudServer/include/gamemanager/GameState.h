#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <memory>
#include <unordered_map>

#include "Area.h"
#include "Player.h"
#include "Room.h"

namespace mudserver {
namespace gamemanager {

using namespace boost::bimaps;
typedef bimap<set_of<CharacterID>, list_of<RoomID>> CharacterRoomLookupTable;
typedef std::map<RoomID, Room&> RoomLookupTable;

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
    vector<Area> areas;

public:
    GameState();

    Room& getCharacterLocation(const Character& character);
    vector<Character> getCharactersInRoom(const Room& room);
    Room& getRoom(const RoomID);
    void addArea(const Area& area);
    void updateCharacterLocation(Character& character, Room& room);

    };

}  // namespace gamemanager
}  // namespace mudserver
#endif  // GAMESTATE_H
