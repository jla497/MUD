#ifndef PLAYER_H
#define PLAYER_H

#include "Server.h"
#include "entities/CharacterEntity.h"
#include <boost/serialization/access.hpp>
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
  private:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar &id;
        ar &username;
        ar &password;
        ar &isAdmin;
    }

    PlayerId id = static_cast<PlayerId>(-1);
    UsernameType username;
    PasswordType password;
    networking::ConnectionId connectionId;
    CharacterEntity *character = nullptr;
    bool isAdmin = false;

  public:
    Player() = default;

    /**
     * The player is constructed with ID, username, and password.
     * @param id the player's ID, currently matching the connection ID
     * @param username the player's username
     * @param password the player's password
     */
    Player(PlayerId id, UsernameType username, PasswordType password);

    /**
     * Gets the player's numeric ID.
     * @return the player's id number
     */
    PlayerId getId() const;
    bool hasAdminPrivilege();
    void getAdminPrivilege();
    UsernameType getUsername() const;
    bool passwordEquals(const PasswordType &password) const;
    networking::ConnectionId getConnectionId() const;
    void setConnectionId(networking::ConnectionId id);
};

} // namespace gamemanager
} // namespace mudserver
#endif // PLAYER_H
