#ifndef PLAYERSERVICE_H
#define PLAYERSERVICE_H

#include <unordered_map>
#include <boost/optional.hpp>
#include "Player.h"

namespace mudserver {
namespace gamemanager{

enum class AddPlayerResult {
    playerAdded,
    playerExists,
    playerInvalid,
    _NUM_RESULTS_
};

class PlayerService {
    PlayerId nextPlayerId;
    std::unordered_map<PlayerId, Player> players;
    std::unordered_map<UsernameType, PlayerId> playerIdByName;

    PlayerId getNextPlayerId();
    PlayerId getPlayerIdByName(const UsernameType &username);
  public:
    PlayerService();
    boost::optional<Player&> identify(UsernameType username, PasswordType password);
    AddPlayerResult addPlayer(UsernameType username, PasswordType password);
};

}
}

#endif //PLAYERSERVICE_H
