#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <chrono>
#include <memory>
#include <unordered_map>
#include <boost/bimap.hpp>

#include "GameState.h"
#include "Player.h"

namespace mudserver {
    
namespace networking {

/* Stubs for testing only */
using ConnectionID = gamemanager::PlayerID;
using PlayerMessageVal = std::string;
typedef struct PlayerMessage {
    ConnectionID id;
    PlayerMessageVal value;
    PlayerMessage(ConnectionID id, PlayerMessageVal value) :
        id{id}, value{value} {} 
} PlayerMessage;

using PlayerMessages = std::unique_ptr<std::vector<PlayerMessage> >;
    
/**
 * Stub implementation of ConnectionManager
 */
class ConnectionManagerStub {
public:
    ConnectionManagerStub() {}
    ~ConnectionManagerStub() {}
    
     std::unique_ptr<std::vector<PlayerMessage> > getMessages () {
        auto messages = std::make_unique<std::vector<PlayerMessage> >();
        messages->push_back(PlayerMessage{42, "hit frog"});
        
        // should be OK to return directly here - compiler can elide copy
        return messages;
    }

};
}   // namespace networking

namespace gamemanager {

using GameLoopTick = std::chrono::milliseconds;
constexpr GameLoopTick kDefaultGameLoopTick = GameLoopTick(1000);

/* Type definitions used in GameManager */
using std::unique_ptr;
using std::vector;
using networking::PlayerMessage;
using networking::PlayerMessageVal;
using networking::ConnectionManagerStub;
    
class GameManager {
    
    unique_ptr<ConnectionManagerStub> connectionManager;
    unique_ptr<GameState> gameState;
    std::unordered_map<PlayerID, Player&> players;
    GameLoopTick tick;
    
    void processMessages(vector<PlayerMessage>& messages);
    
public:
    GameManager();
    GameManager(const GameManager& gm) = delete;
    ~GameManager();
    
    void mainLoop();
};

    
}
}

#endif
