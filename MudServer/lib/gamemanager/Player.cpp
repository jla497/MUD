#include "gamemanager/Player.h"

namespace mudserver {
namespace gamemanager {

Player::Player(PlayerId id, std::string username, std::string password)
    : id{id},
      username{std::move(username)},
      password{std::move(password)},
      character{nullptr} {}

PlayerId Player::getId() const { return id; }

}  // namespace gamemanager
}  // namespace mudserver
