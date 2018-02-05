#ifndef PLAYER_H
#define PLAYER_H

#include "entities/CharacterEntity.h"
#include <string>

namespace mudserver {
namespace gamemanager {

using PlayerId = uintptr_t;

class Player {
    PlayerId id;
    std::string username;
    std::string password;
    CharacterEntity* character;

public:
    /**
     * Default constructor
     */
    Player(PlayerId id, std::string username, std::string password);

    PlayerId getId() const;
};

}  // namespace gamemanager
}  // namespace mudserver
#endif  // PLAYER_H
