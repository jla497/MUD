#ifndef PLAYER_H
#define PLAYER_H

#include "Server.h"
#include "entities/CharacterEntity.h"
#include <string>

namespace mudserver {
namespace gamemanager {

using PlayerId = uintptr_t;
using UsernameType = std::string;
using PasswordType = std::string;

/**
 * The Player is a representation of the human logged in to the server. This is
 * distinct from both the connection, which is owned by the networking layer,
 * and the PlayerCharacter, which is the actual fantasy being in the game world.
 */
class Player {
    PlayerId id;
    std::string username;
    std::string password;
    networking::ConnectionId connectionId;
    CharacterEntity *character;

  public:
    /**
     * The player is constructed with ID, username, and password.
     * @param id the player's ID, currently matching the connection ID
     * @param username the player's username
     * @param password the player's password
     */
    Player(PlayerId id, std::string username, std::string password);

    /**
     * Gets the player's numeric ID.
     * @return the player's id number
     */
    PlayerId getId() const;
    UsernameType getUsername() const;
    bool passwordEquals(const PasswordType &password) const;
    networking::ConnectionId getConnectionId() const;
    void setConnectionId(networking::ConnectionId id);
};

} // namespace gamemanager
} // namespace mudserver
#endif // PLAYER_H
