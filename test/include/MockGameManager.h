#include "connectionmanager/ConnectionManager.h"
#include "gamemanager/GameManager.h"
#include "gmock/gmock.h"
#include "persistence/PersistenceService.h"

class MockGameManager : public mudserver::gamemanager::GameManager {
    mudserver::persistence::PersistenceService ps;

  public:
    MockGameManager(mudserver::connection::ConnectionManager &cm,
                    mudserver::gamemanager::GameState &gs)
        : GameManager(cm, gs, ps), ps{""} {}
};