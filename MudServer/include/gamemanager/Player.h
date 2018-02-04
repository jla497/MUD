#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "entities/CharacterEntity.h"

namespace mudserver {
namespace gamemanager {

using PlayerID = uintptr_t;

class Player {
    PlayerID id;
    std::string username;
    std::string password;
    CharacterEntity* character;

public:
    /**
     * Default constructor
     */
    Player(PlayerID id, std::string username, std::string password);

    CharacterEntity* getCharacter();
};

}  // namespace gamemanager
}  // namespace mudserver
#endif  // PLAYER_H
