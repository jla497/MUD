#include <gtest/gtest.h>

#include "gamemanager/GameState.h"

namespace mudserver {
namespace gamemanager {

class GameStateTest : public testing::Test {
protected:
    virtual void SetUp() {
//        state.addRoomToLUT(room);
//        state.addCharacterToLookUp(character1, room);
//        state.addCharacterToLookUp(character2, room);
    }

    virtual void TearDown() {
        state.clearCharacterRoomLUT();
//        state.clearRoomLUT();
        state.clearAreas();
    }

    Room room{1};
    Character character1{1};
    Character character2{2};
    GameState state;
};

//TEST_F(GameStateTest, AddCharacterWithLocation) {
//    RoomEntity* returnedRoom = state.getCharacterLocation(character1);
//    EXPECT_EQ(returnedRoom->getID(), room.getID());
//}
//
//TEST_F(GameStateTest, GetAllCharactersInRoom) {
//    vector<CharacterID> charIDs= state.getCharactersInRoom(room);
//    EXPECT_EQ(charIDs.size(), 2);
//}
//
//TEST_F(GameStateTest, AddAreaToAreasVector) {
//    Area area;
//    state.addArea(area);
//    vector<Area> areas = state.getAreas();
//    EXPECT_EQ(areas.size(), 1);
//}


}
}  // namespace mudserver