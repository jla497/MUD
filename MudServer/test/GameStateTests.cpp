#include <gtest/gtest.h>

#include "gamemanager/GameState.h"

namespace mudserver {
namespace gamemanager {

class GameStateTest : public testing::Test {
  public:
    // <<<<<<< HEAD
    CharacterEntity createCharacter() {
        int armor = 1;
        std::string damage = "1d8+32";
        std::vector<std::string> desc{};
        desc.push_back("desc1");
        unsigned int exp = 1;
        int gold = 1;
        std::string hit = "1d1+30000";
        std::vector<std::string> keywords{};
        keywords.push_back("keyword1");
        unsigned int level = 1;
        std::vector<std::string> longDesc{};
        longDesc.push_back("desc1");
        std::string shortDesc = "test";
        int thac0 = 1;
        // TODO typeId for player characters
        auto character =
            CharacterEntity(armor, damage, desc, exp, gold, hit, 0, keywords,
                            level, longDesc, shortDesc, thac0);
        return character;
    }

  protected:
    virtual void SetUp() {
        state.initFromYaml({"MudGameEngine/lib/dataFiles/detailed_smurf.yml"});
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
    CharacterEntity *returnedChar = state.getCharacterFromLUT(id);
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
