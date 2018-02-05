#include <gtest/gtest.h>

#include "gamemanager/GameState.h"

namespace mudserver {
namespace gamemanager {

class GameStateTest : public testing::Test {
protected:
    virtual void SetUp() {
        state.parseYamlFile("MudGameEngine/lib/dataFiles/detailed_smurf.yml");
        state.initRoomLUT();
    }

    virtual void TearDown() {
        state.clearCharacterRoomLUT();
        state.clearAreas();
    }

    unsigned int roomId = 101;
    GameState state;
};

TEST_F(GameStateTest, AddCharacterWithLocation) {
    int armor = 1;
    std::string damage = "1";
    std::vector<std::string> desc {};
    desc.push_back("desc1");
    unsigned int exp = 1;
    int gold = 1;
    std::string hit = "1";
    std::vector<std::string> keywords {};
    keywords.push_back("keyword1");
    unsigned int level = 1;
    std::vector<std::string> longDesc {};
    longDesc.push_back("desc1");
    std::string shortDesc = "test";
    int thac0 = 1;
    auto character1 = std::make_unique<PlayerCharacter>(
            armor, damage, desc, exp, gold, hit,
            keywords, level,longDesc, shortDesc, thac0
    );
    RoomEntity* room = state.getRoomFromLUT(roomId);
    state.addCharacterRoomRelationToLUT(character1.get(), room);
    RoomEntity* returnedRoom = state.getCharacterLocation(character1.get());
    EXPECT_EQ(returnedRoom->getId(), room->getId());
}

TEST_F(GameStateTest, GetAllCharactersInRoom) {
    int armor = 1;
    std::string damage = "1";
    std::vector<std::string> desc {};
    desc.push_back("desc1");
    unsigned int exp = 1;
    int gold = 1;
    std::string hit = "1";
    std::vector<std::string> keywords {};
    keywords.push_back("keyword1");
    unsigned int level = 1;
    std::vector<std::string> longDesc {};
    longDesc.push_back("desc1");
    std::string shortDesc = "test";
    int thac0 = 1;
    auto character1 = std::make_unique<PlayerCharacter>(
            armor, damage, desc, exp, gold, hit,
            keywords, level,longDesc, shortDesc, thac0
    );
    auto character2 = std::make_unique<PlayerCharacter>(
            armor, damage, desc, exp, gold, hit,
            keywords, level,longDesc, shortDesc, thac0
    );
    RoomEntity* room = state.getRoomFromLUT(roomId);
    state.addCharacterRoomRelationToLUT(character1.get(), room);
    state.addCharacterRoomRelationToLUT(character2.get(), room);
    vector<UniqueId> charIDs = state.getCharactersInRoom(room);
    EXPECT_EQ(charIDs.size(), 2);
}

TEST_F(GameStateTest, AddAreaToAreasVector) {
    state.addAreaFromParser();
    EXPECT_EQ(state.getAreasVector().size(), 1);
}

TEST_F(GameStateTest, AddNewRoom) {
    std::vector<std::string> desc {};
    desc.push_back("desc1");
    std::vector<std::string> descExt {};
    descExt.push_back("extended desc1");
    std::vector<std::unique_ptr<DoorEntity>> doors {};
    std::vector<std::string> keywordsExt {};
    keywordsExt.push_back("keyword1");
    std::string name("room1");
    auto newRoomId = 1;
    auto room = std::make_unique<RoomEntity>(desc, std::move(doors), descExt, keywordsExt, name, newRoomId);
    state.addRoomToLUT(room.get());
    RoomEntity* addedRoom = state.getRoomFromLUT(newRoomId);
    EXPECT_EQ(room->getId(), addedRoom->getId());
}

TEST_F(GameStateTest, GetCharacterFromString) {
    int armor = 1;
    std::string damage = "1";
    std::vector<std::string> desc {};
    desc.push_back("desc1");
    unsigned int exp = 1;
    int gold = 1;
    std::string hit = "1";
    std::vector<std::string> keywords {};
    keywords.push_back("keyword1");
    unsigned int level = 1;
    std::vector<std::string> longDesc {};
    longDesc.push_back("desc1");
    std::string shortDesc = "test";
    int thac0 = 1;
    auto character = std::make_unique<PlayerCharacter>(
            armor, damage, desc, exp, gold, hit,
            keywords, level,longDesc, shortDesc, thac0
    );
    state.addCharacterToLUT(character.get());
    UniqueId id = character->getEntityId();
    PlayerCharacter* returnedChar = state.getCharacterFromLUT(id);
    EXPECT_EQ(returnedChar->getEntityId(), character->getEntityId());
}

}  // namespace gamemanager
}  // namespace mudserver