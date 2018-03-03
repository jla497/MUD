#include "gamemanager/PlayerService.h"
#include "gamemanager/Player.h"
#include <gtest/gtest.h>

using namespace mudserver::gamemanager;

class PlayerServiceTests : public testing::Test {
  protected:
    PlayerService ps;

  public:
    PlayerServiceTests() = default;
    virtual void SetUp() { PlayerService ps{}; }
};

TEST_F(PlayerServiceTests, AddNewPlayer) {
    auto playerResult = ps.identify("jimbob", "hunter2");
    ASSERT_FALSE(playerResult);

    ASSERT_EQ(ps.addPlayer("jimbob", "hunter2"), AddPlayerResult::playerAdded);
    ASSERT_EQ(ps.addPlayer("jimbob", "hunter3"), AddPlayerResult::playerExists);

    playerResult = ps.identify("jimbob", "hunter2");
    ASSERT_TRUE(playerResult);
    ASSERT_EQ(playerResult->getUsername(), "jimbob");
}

TEST_F(PlayerServiceTests, PasswordCheck) {
    ps.addPlayer("jimbob", "hunter2");
    ASSERT_FALSE(ps.identify("jimbob", "1337"));
    ASSERT_EQ(ps.identify("jimbob", "hunter2")->getUsername(), "jimbob");
}

TEST_F(PlayerServiceTests, PlayerConnectionUpdate) {
    ps.addPlayer("jimbob", "hunter2");
    auto jimbob = ps.identify("jimbob", "hunter2");
    jimbob->setConnectionId(42);

    auto alsoJimbob = ps.identify("jimbob", "hunter2");
    ASSERT_EQ(alsoJimbob->getConnectionId(), 42);
}