#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <boost/bimap.hpp>
#include <chrono>
#include <memory>
#include <unordered_map>
#include <queue>

#include "commandparser/CommandParser.h"
#include "connectionmanager/ConnectionManager.h"
#include "entities/Entity.h"
#include "actions/Action.h"
#include "GameState.h"
#include "Player.h"

namespace mudserver {
namespace gamemanager {

using GameLoopTick = std::chrono::milliseconds;
constexpr GameLoopTick DEFAULT_TICK_LENGTH_MS = GameLoopTick(1000);

using mudserver::commandparser::CommandParser;

/* Type definitions used in GameManager */
using connection::gameAndUserMsgs;
using std::unique_ptr;
using std::vector;

class GameManager {
    GameState gameState;
    GameLoopTick tick;
    bool done;
    CommandParser commandParser;
    connection::ConnectionManager& connectionManager;

    std::unordered_map<PlayerID, Player> players;
    std::queue<connection::gameAndUserInterface> outgoingMessages;
    std::queue<std::unique_ptr<Action>> actions;

    void processMessages(gameAndUserMsgs& messages);
    void enqueueMessage(networking::Connection conn, std::string msg);
    void sendMessagesToPlayers();

    void enqueueAction(unique_ptr<Action> action);
public:
    GameManager(connection::ConnectionManager& connMan);
    GameManager(const GameManager& gm) = delete;

    void mainLoop();
    void performQueuedActions();
};

}  // namespace mudserver
}  // namespace gamemanager

#endif
