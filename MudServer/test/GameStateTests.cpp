#include <gtest/gtest.h>

#include "gamemanager/GameState.h"

namespace mudserver {
namespace gamemanager {

class GameStateTest : public testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {

    }
    Room room{1};
    Character character{1};
    GameState state;
};

TEST_F(GameStateTest, AddCharacterWithLocation) {
    state.addCharacterToLookUp(character, room);
    state.addRoomToLUT(room);
    Room& returnedRoom = state.getCharacterLocation(character);
    EXPECT_EQ(returnedRoom.getID(), room.getID());
}

TEST_F(GameStateTest, AddAreaToAreasVector) {
    Area area;
    state.addArea(area);
    vector<Area> areas = state.getAreas();
    EXPECT_EQ(areas.size(), 1);
}


}
}  // namespace mudserver