#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "MockConnectionManager.h"
#include "MockGameManager.h"
#include "commandparser/CommandParser.h"
#include "entities/CharacterEntity.h"
#include "gamemanager/GameState.h"

#include "actions/AttackAction.h"
#include "actions/MoveAction.h"
#include "actions/NullAction.h"
#include "actions/SayAction.h"

using mudserver::commandparser::CommandParser;
using mudserver::gamemanager::GameState;

class CommandParserTest : public ::testing::Test {
  public:
    CommandParserTest() : cp{}, cm{}, gs{}, gm{cm, gs} {
        pl = Player{42, "jimbob", "hunter2"};
    }

    CommandParser cp;
    MockConnectionManager cm;
    GameState gs;
    MockGameManager gm;
    Player pl;
};

TEST_F(CommandParserTest, parsesSayAction) {
    auto action = cp.actionFromPlayerCommand(pl, "say stuff", gm);
    auto realType = dynamic_cast<SayAction *>(action.get());
    EXPECT_TRUE(realType);
};

TEST_F(CommandParserTest, parsesAttackAction) {
    auto action = cp.actionFromPlayerCommand(pl, "attack frog", gm);
    auto realType = dynamic_cast<AttackAction *>(action.get());
    EXPECT_TRUE(realType);
};

TEST_F(CommandParserTest, parsesMoveAction) {
    auto action = cp.actionFromPlayerCommand(pl, "move north", gm);
    auto realType = dynamic_cast<MoveAction *>(action.get());
    EXPECT_TRUE(realType);
};

TEST_F(CommandParserTest, defaultsToNullAction) {
    auto action = cp.actionFromPlayerCommand(pl, "blarghidibah foo", gm);
    auto realType = dynamic_cast<NullAction *>(action.get());
    EXPECT_TRUE(realType);
};

TEST_F(CommandParserTest, caseInsensitive) {
    auto action1 = cp.actionFromPlayerCommand(pl, "sAy bla", gm);
    auto realType1 = dynamic_cast<SayAction *>(action1.get());
    EXPECT_TRUE(realType1);

    auto action2 = cp.actionFromPlayerCommand(pl, "SAY bla", gm);
    auto realType2 = dynamic_cast<SayAction *>(action2.get());
    EXPECT_TRUE(realType2);
};
