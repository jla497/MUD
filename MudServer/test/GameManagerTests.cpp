#include <gtest/gtest.h>

#include "connectionmanager/ConnectionManager.h"
#include "gamemanager/GameManager.h"
#include "gamemanager/GameState.h"

class GameManagerTests : public testing::Test {
  protected:
    virtual void SetUp() {

        networking::Message m1{networking::Connection{39985500}, "move north"};

        incoming.push_back(m1);

        state.parseYamlFile("MudGameEngine/lib/dataFiles/detailed_smurf.yml");
        state.initRoomLUT();
    }

    virtual void TearDown() {
        state.clearCharacterRoomLUT();
        state.clearAreas();
    }

  public:
    mudserver::connection::ConnectionManager m_manager{4000};
    std::deque<networking::Message> incoming;
    unsigned int rid = 101;
    mudserver::gamemanager::GameState state;
};

TEST_F(GameManagerTests, StartGameManager) {
    networking::Message m1{networking::Connection{39985500}, "move north"};

    incoming.push_back(m1);

    mudserver::persistence::PersistenceService ps{""};

    state.parseYamlFile("MudGameEngine/lib/dataFiles/detailed_smurf.yml");
    state.initRoomLUT();
    m_manager.rxFromServer(incoming);
    mudserver::gamemanager::GameManager gameManager{m_manager, state, ps};
}