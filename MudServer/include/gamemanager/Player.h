#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "entities/PlayerCharacter.h"

namespace mudserver {
namespace gamemanager {

using PlayerID = uintptr_t;

class Player {
    PlayerID id;
    std::string username;
    std::string password;
    PlayerCharacter* character;

public:
    /**
     * Default constructor
     */
    Player(PlayerID id, std::string username, std::string password);

    PlayerCharacter* getCharacter();
};

}  // namespace gamemanager
}  // namespace mudserver
#endif  // PLAYER_H
