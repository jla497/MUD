#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <boost/bimap.hpp>
#include <chrono>
#include <memory>
#include <unordered_map>
#include <queue>

#include "commandparser/CommandParser.h"
#include "ConnectionManager.h"
#include "GameState.h"
#include "Player.h"

namespace mudserver {
namespace gamemanager {

using GameLoopTick = std::chrono::milliseconds;
constexpr GameLoopTick DEFAULT_TICK_LENGTH_MS = GameLoopTick(1000);

using CommandParser = commandparser::CommandParser;

/* Type definitions used in GameManager */
using connection::gameAndUserMsgs;
using std::unique_ptr;
using std::vector;

class GameManager {
    connection::ConnectionManager& connectionManager;
    GameState gameState;
    std::unordered_map<PlayerID, Player> players;
    GameLoopTick tick;

    std::queue<connection::gameAndUserInterface> outgoingMessages;
    CommandParser commandParser;

    void processMessages(gameAndUserMsgs& messages);
    void enqueueMessage(networking::Connection conn, std::string msg);
    void sendMessagesToPlayers();
public:
    explicit GameManager(connection::ConnectionManager& connMan);
    GameManager(const GameManager& gm) = delete;

    void mainLoop();
};

}  // namespace gamemanager
}  // namespace mudserver

#endif
