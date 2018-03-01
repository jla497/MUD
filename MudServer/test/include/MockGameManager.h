#include "connectionmanager/ConnectionManager.h"
#include "gamemanager/GameManager.h"
#include "gmock/gmock.h"

class MockGameManager : public mudserver::gamemanager::GameManager {
  public:
    MockGameManager(mudserver::connection::ConnectionManager &cm,
                    mudserver::gamemanager::GameState &gs)
        : GameManager(cm, gs) {}
};