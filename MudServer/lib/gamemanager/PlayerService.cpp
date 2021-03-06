#include "gamemanager/PlayerService.h"
#include "entities/CharacterEntity.h"
#include "resources/PlayerCharacterDefaults.h"

namespace pc = mudserver::resources::playercharacter;
using namespace mudserver::gamemanager;

Player *PlayerService::identify(UsernameType username, PasswordType password) {
    auto id = getPlayerIdByName(username);
    auto player = players.find(id);

    if (player == players.end() || !player->second.passwordEquals(password)) {
        return nullptr;
    }
    return &player->second;
}

AddPlayerResult PlayerService::addPlayer(UsernameType username,
                                         PasswordType password) {

    if (playerIdByName.find(username) != playerIdByName.end()) {
        return AddPlayerResult::playerExists;
    }

    if (!userAndPassAreValid(username, password)) {
        return AddPlayerResult::playerInvalid;
    }

    PlayerId id = getNextPlayerId();
    Player player{id, username, std::move(password)};
    if (!players.size()) {
        player.getAdminPrivilege();
    }
    playerIdByName[username] = id;
    players.emplace(std::make_pair(id, player));

    return AddPlayerResult::playerAdded;
}

bool PlayerService::userAndPassAreValid(UsernameType username,
                                        PasswordType password) {
    return (username != "" && password != "");
}

PlayerId PlayerService::getNextPlayerId() { return ++nextPlayerId; }

PlayerId PlayerService::getPlayerIdByName(const UsernameType &username) {
    auto id = playerIdByName.find(username);
    if (id != playerIdByName.end()) {
        return id->second;
    } else {
        return 0;
    }
}
PlayerService::PlayerService() : nextPlayerId{1} {}

Player *
PlayerService::getPlayerByConnection(networking::ConnectionId connectionId) {
    auto idPair = playerIdByConnection.find(connectionId);
    if (idPair != playerIdByConnection.end()) {
        return &players.at(idPair->second);
    } else {
        return nullptr;
    }
}

const UniqueId *PlayerService::playerToCharacter(PlayerId playerId) {
    auto entry = playerCharacterBimap.left.find(playerId);
    if (entry != playerCharacterBimap.left.end()) {
        return &entry->second;
    }

    return nullptr;
}

PlayerId PlayerService::characterToPlayer(UniqueId characterId) {
    return playerCharacterBimap.right.find(characterId)->second;
}

CharacterEntity PlayerService::createPlayerCharacter(PlayerId playerId) {
    auto testShortDesc =
        "TestPlayerName" + std::to_string(playerCharacterBimap.size());

    CharacterEntity character{pc::ARMOR,
                              std::string{pc::DAMAGE},
                              std::vector<std::string>{},
                              pc::EXP,
                              pc::GOLD,
                              std::string{pc::HIT},
                              pc::TYPEID,
                              std::vector<std::string>{},
                              pc::LEVEL,
                              std::vector<std::string>{},
                              testShortDesc,
                              pc::THAC0};
    character.set_isPlayerCharacter();
    playerCharacterBimap.insert(
        PcBmType::value_type(playerId, character.getEntityId()));
    return character;
}

void PlayerService::setPlayerConnection(PlayerId playerId,
                                        networking::ConnectionId connectionId) {
    playerIdByConnection[connectionId] = playerId;
    auto player = getPlayerById(playerId);
    if (player) {
        player->setConnectionId(connectionId);
    }
}

networking::ConnectionId PlayerService::getPlayerConnection(PlayerId playerId) {
    auto player = getPlayerById(playerId);
    if (player) {
        return player->getConnectionId();
    }
    return 0;
}

Player *PlayerService::getPlayerById(PlayerId playerId) {
    auto playerPair = players.find(playerId);
    if (playerPair != players.end()) {
        return &playerPair->second;
    }
    return nullptr;
}

void PlayerService::updatePlayerCharacterMapping(PlayerId playerId,
                                                 UniqueId characterId) {
    auto it = playerCharacterBimap.left.find(playerId);
    if (it != playerCharacterBimap.left.end()) {
        playerCharacterBimap.left.replace_data(it, characterId);
    }
}

CharacterController *PlayerService::playerToController(PlayerId playerId) {
    auto entry = controllers.find(playerId);
    if (entry != controllers.end()) {
        return entry->second.get();
    }
    return nullptr;
}

CharacterController *PlayerService::createController(PlayerId playerId) {
    auto controller = std::make_unique<PlayerController>();
    controllers[playerId] = std::move(controller);
    return playerToController(playerId);
}
