#include "gmock/gmock.h"
#include "gamemanager/GameManager.h"
#include "connectionmanager/ConnectionManager.h"

class MockGameManager : public mudserver::gamemanager::GameManager {
public:
    MockGameManager(mudserver::connection::ConnectionManager &cm)
        : GameManager(cm) {}
};