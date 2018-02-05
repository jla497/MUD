#include "gamemanager/Player.h"

namespace mudserver {
	namespace gamemanager {

		Player::Player(PlayerID id, std::string username, std::string password) :
		id{id},
		username{username},
		password{password},
		character{nullptr} {}

		PlayerCharacter* Player::getCharacter() { return character; }

}  // namespace gamemanager
}  // namespace mudserver
