#include "gmock/gmock.h"
#include "gamemanager/GameManager.h"

class MockGameManager : public mudserver::gamemanager::GameManager {
public:
    MockGameManager() = default;
};