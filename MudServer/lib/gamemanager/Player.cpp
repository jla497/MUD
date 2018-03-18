#include "gamemanager/Player.h"
#include <Server.h>
extern "C" {
#include "gamemanager/sha256.h"
}
namespace mudserver {
namespace gamemanager {
std::string sha256str(std::string str);
Player::Player(PlayerId id, std::string username, std::string password)
    : id{id}, username{std::move(username)}, password{sha256str(password)},
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
void hashtostr(char *hash, char * str, int length)
{
	int i = 0,j = 0;
	const char letters[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	for (i=0; i<length; i++)
	{
		unsigned char val = hash[i];
		str[j+1] = letters[val & 0xf];
		str[j] = letters[val >> 4];
		j += 2;
	}
	str[j] = 0;
}
std::string sha256str(std::string str)
{
	SHA256_CTX ctx;
	unsigned char hash[32];
	char str2[129];	
	sha256_init(&ctx);
	sha256_update(&ctx, (unsigned char*)str.c_str(), str.length());
	sha256_final(&ctx, hash);
	hashtostr((char*)hash, (char*)str2,32);
	return std::string((char*)str2);
}

} // namespace gamemanager
} // namespace mudserver
