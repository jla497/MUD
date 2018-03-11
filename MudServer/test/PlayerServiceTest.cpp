#include "gamemanager/PlayerService.h"
#include "gamemanager/Player.h"
#include "persistence/PersistenceService.h"
#include <gtest/gtest.h>

using namespace mudserver::gamemanager;
using namespace mudserver::persistence;

class PlayerServiceTests : public testing::Test {
  protected:
    PlayerService ps;

  public:
    PlayerServiceTests() = default;
    virtual void SetUp() { ps = PlayerService{}; }
};

TEST_F(PlayerServiceTests, AddNewPlayer) {
    auto playerResult = ps.identify("jimbob", "hunter2");
    ASSERT_FALSE(playerResult);

    ASSERT_EQ(ps.addPlayer("jimbob", "hunter2"), AddPlayerResult::playerAdded);
    ASSERT_EQ(ps.addPlayer("jimbob", "hunter3"), AddPlayerResult::playerExists);

    playerResult = ps.identify("jimbob", "hunter2");
    ASSERT_TRUE(playerResult != nullptr);
    ASSERT_EQ(playerResult->getUsername(), "jimbob");
}

TEST_F(PlayerServiceTests, PasswordCheck) {
    ps.addPlayer("jimbob", "hunter2");
    ASSERT_FALSE(ps.identify("jimbob", "1337"));
    auto jimbob = ps.identify("jimbob", "hunter2");
    ASSERT_EQ(jimbob->getUsername(), "jimbob");
}

TEST_F(PlayerServiceTests, PlayerConnectionUpdate) {
    ps.addPlayer("jimbob", "hunter2");
    auto jimbob = ps.identify("jimbob", "hunter2");
    jimbob->setConnectionId(42);

    auto alsoJimbob = ps.identify("jimbob", "hunter2");
    ASSERT_EQ(alsoJimbob->getConnectionId(), 42);
}

TEST_F(PlayerServiceTests, WriteReadPlayers) {
    PersistenceService pss("config");
    ps.addPlayer("jimbob", "hunter2");
    pss.save(ps, "test.dat");
    ps = pss.loadPlayerService("test.dat");
    ASSERT_EQ(ps.identify("jimbob", "hunter2")->getUsername(), "jimbob");
}

TEST_F(PlayerServiceTests, CreatePlayerCharacter) {
    ps.addPlayer("jimbob", "hunter2");
    auto player = ps.identify("jimbob", "hunter2");
    auto playerId = player->getId();
    ps.createPlayerCharacter(playerId);
    ASSERT_TRUE(ps.playerToCharacter(playerId));
}