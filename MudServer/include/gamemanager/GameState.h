#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <memory>
#include <unordered_map>
#include <boost/bimap.hpp>

#include "Player.h"
#include "Room.h"

namespace mudserver {
namespace gamemanager {

// typedef boost::bimap<Character&, Room&> CharacterRoomLookup;
using std::unique_ptr;
using std::unordered_map;

/**
 * The overarching idea of GameState is that it should
 *      - be owned by the GameManager
 *      - own all the information required to save/serialize a game
 *      - be the source of truth for all state relating to the world
 */
class GameState
{
    unordered_map<PlayerID, unique_ptr<Player> > players;
public:
    /**
     * Default constructor
     */
    GameState();
    
    Player* getPlayerByID(const PlayerID id);
    Room& getCharacterLocation(const Character& character);
};

}   //namespace gamemanager
}   //namespace mudserver
#endif // GAMESTATE_H
