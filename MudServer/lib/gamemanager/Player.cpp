#include "gamemanager/Player.h"

namespace mudserver {
namespace gamemanager {

Player::Player(PlayerId id, std::string username, std::string password)
    : id{id}, username{std::move(username)}, password{std::move(password)},
      character{nullptr} {}

PlayerId Player::getId() const { return id; }
bool Player::hasAdminPrivilege() { return isAdmin; }
void Player::getAdminPrivilege() { isAdmin = true; }
} // namespace gamemanager
} // namespace mudserver
