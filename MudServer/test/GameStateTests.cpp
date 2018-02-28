#include <gtest/gtest.h>

#include "gamemanager/GameState.h"

namespace mudserver {
namespace gamemanager {

class GameStateTest : public testing::Test {
  public:
    PlayerCharacter createCharacter() {
        return {
            1,            // armor
            "1",          // damage
            {"desc1"},    // desc
            1,            // exp
            1,            // gold
            "1",          // hit
            {"keyword1"}, // keywords
            1,            // level
            {"desc1"},    // longdesc
            "shortdesc",  // shortdesc
            1             // thac0
        };
    }

  protected:
    virtual void SetUp() {
        state.initFromYaml("MudGameEngine/lib/dataFiles/detailed_smurf.yml");
    }

    virtual void TearDown() {
        state.clearCharacterRoomLUT();
        state.clearAreas();
    }

    unsigned int roomId = 101;
    GameState state;
};

TEST_F(GameStateTest, AddCharacterWithLocation) {
    auto character = createCharacter();
    RoomEntity *room = state.getRoomFromLUT(roomId);
    assert(room != nullptr);
    state.addCharacterRoomRelationToLUT(character.getEntityId(), room->getId());
    RoomEntity *returnedRoom = state.getCharacterLocation(character);
    assert(returnedRoom != nullptr);
    EXPECT_EQ(returnedRoom->getId(), room->getId());
}

TEST_F(GameStateTest, GetAllCharactersInRoom) {
    auto character1 = createCharacter();
    auto character2 = createCharacter();
    RoomEntity *room = state.getRoomFromLUT(roomId);
    state.addCharacterRoomRelationToLUT(character1.getEntityId(),
                                        room->getId());
    state.addCharacterRoomRelationToLUT(character2.getEntityId(),
                                        room->getId());
    std::vector<UniqueId> charIDs = state.getCharactersInRoom(room);
    EXPECT_EQ(charIDs.size(), 2);
}

TEST_F(GameStateTest, AddAreaToAreasVector) {
    state.addAreaFromParser();
    EXPECT_EQ(state.getAreas().size(), 2);
}

TEST_F(GameStateTest, AddNewRoom) {
    RoomEntity room = {
        {"desc1"},          // desc
        {},                 // doors
        {"extended desc1"}, // extended desc
        {"keyword1"},       // extended keywords
        "room1",            // name
        1                   // id
    };

    state.addRoomToLUT(room);
    RoomEntity *addedRoom = state.getRoomFromLUT(1);
    EXPECT_EQ(room.getId(), addedRoom->getId());
}

TEST_F(GameStateTest, GetCharacterFromString) {
    auto character = createCharacter();
    UniqueId id = character.getEntityId();
    state.addCharacter(character);
    PlayerCharacter *returnedChar = state.getCharacterFromLUT(id);
    EXPECT_EQ(returnedChar->getEntityId(), id);
}

TEST_F(GameStateTest, TestUpdatePlayerRoom) {
    auto character = createCharacter();
    RoomEntity *room = state.getRoomFromLUT(roomId);
    state.addCharacterRoomRelationToLUT(character.getEntityId(), room->getId());
    std::vector<UniqueId> charIDs = state.getCharactersInRoom(room);
    EXPECT_EQ(charIDs.size(), 1);
    room = state.getRoomFromLUT(roomId + 1);
    state.addCharacterRoomRelationToLUT(character.getEntityId(), room->getId());
    charIDs = state.getCharactersInRoom(room);
    EXPECT_EQ(charIDs.size(), 1);
}

} // namespace gamemanager
} // namespace mudserver
