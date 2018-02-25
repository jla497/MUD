#include "gamemanager/PlayerService.h"

using namespace mudserver::gamemanager;

boost::optional<Player&> PlayerService::identify(UsernameType username,
                                PasswordType password) {
    auto id = getPlayerIdByName(username);
    auto player = players.find(id);

    if (player != players.end() && player->second.passwordEquals(password)) {
        return player->second;
    } else {
        return boost::none;
    }
}

AddPlayerResult PlayerService::addPlayer(UsernameType username,
                                         PasswordType password) {
    PlayerId id = getNextPlayerId();
    Player player{id, username, std::move(password)};
    playerIdByName[username] = id;
    players.emplace(std::make_pair(
        id, player));

    return AddPlayerResult::playerAdded;
}

PlayerId PlayerService::getNextPlayerId() {
    return ++nextPlayerId;
}

PlayerId PlayerService::getPlayerIdByName(const UsernameType &username) {
    auto id = playerIdByName.find(username);
    if (id != playerIdByName.end()) {
        return id->second;
    } else {
        return 0;
    }
}
PlayerService::PlayerService() : nextPlayerId{1} {

}

