#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "MockConnectionManager.h"
#include "MockGameManager.h"
#include "commandparser/CommandParser.h"
#include "entities/PlayerCharacter.h"
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
        int armor = 1;
        std::string damage = "1";
        std::vector<std::string> desc{};
        desc.push_back("desc1");
        unsigned int exp = 1;
        int gold = 1;
        std::string hit = "1";
        std::vector<std::string> keywords{};
        keywords.push_back("keyword1");
        unsigned int level = 1;
        std::vector<std::string> longDesc{};
        longDesc.push_back("desc1");
        std::string shortDesc = "test";
        int thac0 = 1;

        ch = PlayerCharacter{armor,    damage, desc,     exp,       gold, hit,
                             keywords, level,  longDesc, shortDesc, thac0};
    }

    CommandParser cp;
    MockConnectionManager cm;
    GameState gs;
    MockGameManager gm;
    PlayerCharacter ch;
};

TEST_F(CommandParserTest, parsesSayAction) {
    auto action = cp.actionFromPlayerCommand(ch, "say stuff", gm);
    auto realType = dynamic_cast<SayAction*>(action.get());
    EXPECT_TRUE(realType);
};

TEST_F(CommandParserTest, parsesAttackAction) {
    auto action = cp.actionFromPlayerCommand(ch, "attack frog", gm);
    auto realType = dynamic_cast<AttackAction*>(action.get());
    EXPECT_TRUE(realType);
};

TEST_F(CommandParserTest, parsesMoveAction) {
    auto action = cp.actionFromPlayerCommand(ch, "move north", gm);
    auto realType = dynamic_cast<MoveAction*>(action.get());
    EXPECT_TRUE(realType);
};

TEST_F(CommandParserTest, defaultsToNullAction) {
    auto action = cp.actionFromPlayerCommand(ch, "blarghidibah foo", gm);
    auto realType = dynamic_cast<NullAction*>(action.get());
    EXPECT_TRUE(realType);
};

TEST_F(CommandParserTest, caseInsensitive) {
    auto action1 = cp.actionFromPlayerCommand(ch, "sAy bla", gm);
    auto realType1 = dynamic_cast<SayAction*>(action1.get());
    EXPECT_TRUE(realType1);

    auto action2 = cp.actionFromPlayerCommand(ch, "SAY bla", gm);
    auto realType2 = dynamic_cast<SayAction*>(action2.get());
    EXPECT_TRUE(realType2);
};
