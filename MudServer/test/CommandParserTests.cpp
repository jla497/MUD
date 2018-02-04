#include <memory>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "commandparser/CommandParser.h"
#include "MockCharacter.h"
#include "MockGameManager.h"
#include "actions/SayAction.h"

using mudserver::commandparser::CommandParser;

TEST(CommandParserTest, actionFromPlayerCommand_createsCorrectTests) {
    CommandParser cp{};
    MockGameManager gm{};
    auto ch = std::make_unique<MockCharacter>();

    auto action = cp.actionFromPlayerCommand(ch.get(), "say stuff", gm);
    auto realType = dynamic_cast<SayAction*>(*action);
    EXPECT_TRUE(realType);
};