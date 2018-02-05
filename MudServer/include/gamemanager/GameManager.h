#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <boost/bimap.hpp>
#include <chrono>
#include <memory>
#include <queue>
#include <unordered_map>

#include "Character.h"
#include "GameState.h"
#include "Player.h"
#include "UniqueId.h"
#include "actions/Action.h"
#include "commandparser/CommandParser.h"
#include "connectionmanager/ConnectionManager.h"
#include "entities/CharacterEntity.h"
#include "entities/Entity.h"
#include "entities/PlayerCharacter.h"

namespace mudserver {
namespace gamemanager {

using GameLoopTick = std::chrono::milliseconds;
using PcBmType = boost::bimap<PlayerId, UniqueId>;
constexpr GameLoopTick DEFAULT_TICK_LENGTH_MS = GameLoopTick(1000);

using mudserver::commandparser::CommandParser;

/* Type definitions used in GameManager */
using connection::gameAndUserMsgs;
using std::unique_ptr;
using std::vector;

class GameManager {
    GameState& gameState;
    GameLoopTick tick;
    bool done;
    CommandParser commandParser;
    connection::ConnectionManager& connectionManager;

    std::unordered_map<PlayerId, Player> players;
    PcBmType playerCharacterBimap;
    std::queue<connection::gameAndUserInterface> outgoingMessages;
    std::queue<std::unique_ptr<Action>> actions;

    void processMessages(gameAndUserMsgs& messages);
    void enqueueMessage(networking::Connection conn, std::string msg);
    void sendMessagesToPlayers();

    void enqueueAction(unique_ptr<Action> action);
    void performQueuedActions();

    PlayerCharacter* playerToCharacter(const Player& player);
    PlayerCharacter* playerIdToCharacter(PlayerId playerId);
    Player& characterToPlayer(const PlayerCharacter& character);
    Player& characterIdToPlayer(UniqueId characterId);

public:
    GameManager(connection::ConnectionManager& connMan,
                    GameState& gameState);
    GameManager(const GameManager& gm) = delete;
    void mainLoop();
    GameState &getState();

    void sendCharacterMessage(UniqueId characterId, std::string message);
    void addPlayerCharacter(PlayerId playerId);
};

}  // namespace gamemanager
}  // namespace mudserver

#endif
