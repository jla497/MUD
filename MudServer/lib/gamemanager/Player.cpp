#include "gamemanager/Player.h"
#include <Server.h>

namespace mudserver {
namespace gamemanager {

Player::Player(PlayerId id, std::string username, std::string password)
    : id{id}, username{std::move(username)}, password{std::move(password)},
      character{nullptr}, connectionId{0} {}

PlayerId Player::getId() const { return id; }
UsernameType Player::getUsername() const { return username; }

bool Player::passwordEquals(const PasswordType &password) const {
    return password == this->password;
}

networking::ConnectionId Player::getConnectionId() const {
    return connectionId;
}
void Player::setConnectionId(networking::ConnectionId id) { connectionId = id; }

} // namespace gamemanager
} // namespace mudserver
