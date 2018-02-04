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

    RoomID roomId = 101;
    Character character1{1};
    Character character2{2};
    GameState state;
};

TEST_F(GameStateTest, AddCharacterWithLocation) {
    RoomEntity* room = state.getRoomFromLUT(roomId);
    state.addCharacterToLookUp(character1, room);
    RoomEntity* returnedRoom = state.getCharacterLocation(character1);
    EXPECT_EQ(returnedRoom->getId(), room->getId());
}

TEST_F(GameStateTest, GetAllCharactersInRoom) {
    RoomEntity* room = state.getRoomFromLUT(roomId);
    state.addCharacterToLookUp(character1, room);
    state.addCharacterToLookUp(character2, room);
    vector<CharacterID> charIDs = state.getCharactersInRoom(room);
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
    RoomID newRoomId = 1;
    auto room = std::make_unique<RoomEntity>(desc, std::move(doors), descExt, keywordsExt, name, newRoomId);
    state.addRoomToLUT(room.get());
    RoomEntity* addedRoom = state.getRoomFromLUT(newRoomId);
    EXPECT_EQ(room->getId(), addedRoom->getId());
}

}  // namespace gamemanager
}  // namespace mudserver