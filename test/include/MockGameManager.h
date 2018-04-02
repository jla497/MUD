#include "connectionmanager/ConnectionManager.h"
#include "gamemanager/GameManager.h"
#include "persistence/PersistenceService.h"
#include "gmock/gmock.h"

class MockGameManager : public mudserver::gamemanager::GameManager {
    mudserver::persistence::PersistenceService ps;

  public:
    MockGameManager(mudserver::connection::ConnectionManager &cm,
                    mudserver::gamemanager::GameState &gs)
        : GameManager(cm, gs, ps), ps{""} {}
};