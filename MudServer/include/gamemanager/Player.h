#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Character.h"

namespace mudserver {
namespace gamemanager {
    
using PlayerID = uintptr_t;
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
    
    Character* getCharacter();
};

}   // namespace gamemanager
}   // namespace mudserver
#endif // PLAYER_H
