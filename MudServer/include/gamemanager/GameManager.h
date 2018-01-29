#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <memory>
#include <unordered_map>
#include <boost/bimap.hpp>
#include <chrono>

#include "GameState.h"
#include "Player.h"
#include "ConnectionManager.h"

namespace mudserver {
namespace gamemanager {

using GameLoopTick = std::chrono::milliseconds;
constexpr GameLoopTick kDefaultGameLoopTick = GameLoopTick(1000);

/* Type definitions used in GameManager */
using std::unique_ptr;
using std::vector;
using connection::gameAndUserMsgs;
    
class GameManager {
    
    unique_ptr<connection::ConnectionManager> connectionManager;
    unique_ptr<GameState> gameState;
    std::unordered_map<PlayerID, Player&> players;
    GameLoopTick tick;
    
    void processMessages(gameAndUserMsgs& messages);
    
public:
    GameManager();
    GameManager(const GameManager& gm) = delete;
    
    void mainLoop();
};

    
}
}

#endif
