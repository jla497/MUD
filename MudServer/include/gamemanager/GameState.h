#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <boost/bimap.hpp>
#include <memory>
#include <unordered_map>

#include "Area.h"
#include "Player.h"
#include "Room.h"

namespace mudserver {
namespace gamemanager {

typedef boost::bimap<CharacterID , RoomID> CharacterRoomLookupTable;
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
public:
    /**
     * Default constructor
     */
    GameState();

    CharacterRoomLookupTable characterRoomLookUp;
    RoomLookupTable roomLookUp;
    vector<Area> areas;

    Room& getCharacterLocation(const Character& character);

    vector<Character> getCharactersFromRoom(const Room& room);
    Room& getRoomFromID(const RoomID);
    Room& getRoomFromCharacter(const Character& character);


    };

}  // namespace gamemanager
}  // namespace mudserver
#endif  // GAMESTATE_H
