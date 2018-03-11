#include "gamemanager/Player.h"
#include <Server.h>

namespace mudserver {
namespace gamemanager {

Player::Player(PlayerId id, std::string username, std::string password)
    : id{id}, username{std::move(username)}, password{std::move(password)},
      connectionId{0}, character{nullptr} {}

PlayerId Player::getId() const { return id; }
UsernameType Player::getUsername() const { return username; }

bool Player::passwordEquals(const PasswordType &password) const {
    return password == this->password;
}

networking::ConnectionId Player::getConnectionId() const {
    return connectionId;
}
void Player::setConnectionId(networking::ConnectionId id) { connectionId = id; }

bool Player::hasAdminPrivilege() { return isAdmin; }
void Player::getAdminPrivilege() { isAdmin = true; }
} // namespace gamemanager
} // namespace mudserver
