#include <gtest/gtest.h>

#include "connectionmanager/ConnectionManager.h"
#include "gamemanager/GameManager.h"
#include "gamemanager/GameState.h"

class EntitiesTests : public testing::Test {
protected:
    virtual void SetUp() {
//        state.parseAreaYamlFile(
//                "MudGameEngine/lib/dataFiles/detailed_smurf.yml");
//        state.initRoomLUT();
    }

    virtual void TearDown() {
//        state.clearCharacterRoomLUT();
//        state.clearAreas();
    }

    const unsigned int DEFAULT_ID = 1;
    const std::string DEFAULT_NAME = "test";
    std::vector<std::string> DEFAULT_DESC = {"test"};
    std::vector<std::string> DEFAULT_KW = {"test"};
    std::string DEFAULT_DIRECTION = "west";

public:
    CharacterEntity createCharacter() {
        int armor = 1;
        std::string damage = "1d8+32";
        unsigned int exp = 1;
        int gold = 1;
        std::string hit = "1d1+30000";
        unsigned int level = 1;
        std::string shortDesc = "test";
        int thac0 = 1;
        return CharacterEntity{
                armor, damage, DEFAULT_DESC, exp, gold,
                hit, 0, DEFAULT_KW, level, DEFAULT_DESC,
                shortDesc, thac0
        };
    }

    RoomEntity createRoom() {
        std::vector<std::string> desc = DEFAULT_DESC;
        std::vector<DoorEntity> doors{};
        std::vector<std::string> descExt{};
        std::vector<std::string> keywordsExt{};
        std::string name = DEFAULT_NAME;
        unsigned int roomId = DEFAULT_ID;
        return RoomEntity{
                desc,
                doors,
                descExt,
                keywordsExt,
                name,
                roomId
        };
    }

    AreaEntity createArea() {
        std::string name = "testArea";
        std::deque<RoomEntity> rooms{};
        return AreaEntity{};
    }

    DoorEntity createDoor() {
        std::vector<std::string> keywords{};
        return DoorEntity{DEFAULT_DESC,
                          DEFAULT_DIRECTION,
                          DEFAULT_KW,
                          DEFAULT_ID};
    }

    ObjectEntity createObject() {
        std::vector<std::string> attributes{};
        unsigned int cost = 1;
        unsigned int objectTypeId = 1;
        std::string itemType = "none";
        std::vector<std::string> descExtra{};
        std::vector<std::string> keywordsExtra{};
        std::string shortDesc = "short";
        std::vector<std::string> wearFlags{};
        int weight = 1;
        return ObjectEntity{
                attributes,
                cost,
                descExtra,
                keywordsExtra,
                objectTypeId,
                itemType,
                DEFAULT_KW,
                DEFAULT_DESC,
                shortDesc,
                wearFlags,
                weight
        };
    }


};


/*************************************
 * Area Tests
 *************************************/

/*************************************
 * Character Tests
 *************************************/

/*************************************
 * Door Tests
 *************************************/

TEST_F(EntitiesTests, GetDoorDirection) {
    DoorEntity door = createDoor();
    EXPECT_EQ(DEFAULT_DIRECTION, door.getDir());
}

/*************************************
 * Object Tests
 *************************************/

/*************************************
 * Room Tests
 *************************************/

TEST_F(EntitiesTests, GetRoomId) {
    RoomEntity room = createRoom();
    EXPECT_EQ(DEFAULT_ID, room.getId());
}

TEST_F(EntitiesTests, GetRoomName) {
    RoomEntity room = createRoom();
    EXPECT_EQ(DEFAULT_NAME, room.getName());
}

TEST_F(EntitiesTests, GetRoomDesc) {
    RoomEntity room = createRoom();
    EXPECT_EQ(DEFAULT_DESC, room.getDesc());
}

//TEST_F(EntitiesTests, GetDestRoomIdOf) {
//    RoomEntity room = createRoom();
//    EXPECT_EQ(DEFAULT_DESC, room.getDestRoomIdOf("west"));
//}

