#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Character.h"

namespace mudserver {
namespace gamemanager {
    
using PlayerID = int;
/**
 */
class Player
{
    PlayerID id;
    std::string username;
    std::string password;
    Character* character;
    
public:
    /**
     * Default constructor
     */
    Player(PlayerID id, std::string username, std::string password);

    /**
     * Destructor
     */
    ~Player();
    
    Character* getCharacter();
};

}   // namespace gamemanager
}   // namespace mudserver
#endif // PLAYER_H
