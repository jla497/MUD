#include "Spell.h"
#include "SpellParser.h"
#include <gtest/gtest.h>

class SpellTests : public testing::Test {
    void SetUp() override {
        Spell spell;
        Spell::DisplayMessages messages;
        messages.hitchar =
            "$N's armor begins to glow softly as it is enhanced by a cantrip.";
        spell.setDisplayMessages(messages);
        spells.push_back(spell);
        parser.loadYamlFile("MudGameEngine/lib/dataFiles/spells.yml");
    }

    void TearDown() override {}

  public:
    std::vector<Spell> spells{};
    SpellParser parser;
};

TEST_F(SpellTests, TestLoadYamlFile) {
    SpellParser spellParser;
    parser.loadYamlFile("MudGameEngine/lib/dataFiles/spells.yml");
}

TEST_F(SpellTests, TestGetAllSpells) { auto spells = parser.getAllSpells(); }

TEST_F(SpellTests, TestGetHitCharVictimName) {
    Spell::DisplayMessages testMessage =
        spells.at(0).getDisplayMessages("", "Smurf", "");
    EXPECT_EQ(
        "Smurf's armor begins to glow softly as it is enhanced by a cantrip.",
        testMessage.hitchar);
}
