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
    std::vector<std::unique_ptr<RoomEntity>> rooms;
    unsigned int roomId = 101;
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
    Area area;
    state.addArea(area);
    vector<Area> areas = state.getAreas();
    EXPECT_EQ(areas.size(), 1);
}


}  // namespace gamemanager
}  // namespace mudserver