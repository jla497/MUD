// #include <memory>

// #include "gtest/gtest.h"
// #include "gmock/gmock.h"

// #include "commandparser/CommandParser.h"
// #include "MockCharacter.h"
// #include "MockGameManager.h"
// #include "MockConnectionManager.h"

// #include "actions/AttackAction.h"
// #include "actions/MoveAction.h"
// #include "actions/NullAction.h"
// #include "actions/SayAction.h"

// using mudserver::commandparser::CommandParser;

// class CommandParserTest : public ::testing::Test {
// public:
//     CommandParserTest()
//         : cp{}, cm{}, gm{cm}, ch{} {}

//     CommandParser cp;
//     MockConnectionManager cm;
//     MockGameManager gm;
//     MockCharacter ch;
// };


// TEST_F(CommandParserTest, parsesSayAction) {
//     auto action = cp.actionFromPlayerCommand(&ch, "say stuff", gm);
//     auto realType = dynamic_cast<SayAction*>(action.get());
//     EXPECT_TRUE(realType);
// };

// TEST_F(CommandParserTest, parsesAttackAction) {
//     auto action = cp.actionFromPlayerCommand(&ch, "attack frog", gm);
//     auto realType = dynamic_cast<AttackAction*>(action.get());
//     EXPECT_TRUE(realType);
// };

// TEST_F(CommandParserTest, parsesMoveAction) {
//     auto action = cp.actionFromPlayerCommand(&ch, "move north", gm);
//     auto realType = dynamic_cast<MoveAction*>(action.get());
//     EXPECT_TRUE(realType);
// };

// TEST_F(CommandParserTest, defaultsToNullAction) {
//     auto action = cp.actionFromPlayerCommand(&ch, "blarghidibah foo", gm);
//     auto realType = dynamic_cast<NullAction*>(action.get());
//     EXPECT_TRUE(realType);
// };

// TEST_F(CommandParserTest, caseInsensitive) {
//     auto action1 = cp.actionFromPlayerCommand(&ch, "sAy bla", gm);
//     auto realType1 = dynamic_cast<SayAction*>(action1.get());
//     EXPECT_TRUE(realType1);

//     auto action2 = cp.actionFromPlayerCommand(&ch, "SAY bla", gm);
//     auto realType2 = dynamic_cast<SayAction*>(action2.get());
//     EXPECT_TRUE(realType2);
// };