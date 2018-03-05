#include "SpellParser.h"
#include "Spell.h"
#include <gtest/gtest.h>

class SpellTests : public testing::Test {
    void SetUp() override {
        Spell spell;
        spell.setHitChar("$N's armor begins to glow softly as it is enhanced by a cantrip.");
        spells.push_back(spell);
        parser.loadYamlFile("MudGameEngine/lib/dataFiles/spells.yml");
    }

    void TearDown() override {}

  public:
    std::vector<Spell> spells{};
    SpellParser parser;
};

TEST_F(SpellTests, TestGetAllDefenseSpells) { 
    auto defSpells = parser.getAllDefenseSpells(); 
}

TEST_F(SpellTests, TestGetAllOffenseSpells) {
    auto offenseSpells = parser.getAllOffenseSpells();
}

TEST_F(SpellTests, TestGetHitCharVictimName) {
    std::string hitChar = spells.at(0).getHitChar("", "Smurf", "");
    EXPECT_EQ("Smurf's armor begins to glow softly as it is enhanced by a cantrip.", hitChar);
}
