#include <gtest/gtest.h>

#include "connectionmanager/ConnectionManager.h"
#include "gamemanager/GameManager.h"

class EntitiesTests : public testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    const int DEFAULT_WEIGHT = 1;
    const int DEFAULT_ARMOR = 1;
    const int DEFAULT_GOLD = 1;
    const int DEFAULT_THAC0 = 1;
    const unsigned int DEFAULT_EXP = 1;
    const unsigned int DEFAULT_ID = 1;
    const unsigned int DEFAULT_COST = 1;
    const unsigned int DEFAULT_OTYPEID = 1;
    const unsigned int DEFAULT_LEVEL = 1;
    const std::string DEFAULT_NAME = "test";
    const std::string DEFAULT_DMG = "1d8+32";
    const std::string DEFAULT_HIT = "1d1+30000";
    std::vector<std::string> DEFAULT_DESC = {"test"};
    std::vector<std::string> DEFAULT_KW = {"test"};
    std::string DEFAULT_DIRECTION = "west";
    std::string DEFAULT_SHORTDESC = "test";
    std::string DEFAULT_ITEMTYPE = "test";
    std::vector<std::string> DEFAULT_DESCEXT = {"test"};
    std::vector<std::string> DEFAULT_KWEXT = {"test"};
    std::vector<std::string> DEFAULT_ATTR = {"none"};
    std::vector<std::string> DEFAULT_WEARFLAGS = {"none"};

public:
    CharacterEntity createCharacter() {
        return CharacterEntity{
                DEFAULT_ARMOR, DEFAULT_DMG,
                DEFAULT_DESC, DEFAULT_EXP,
                DEFAULT_GOLD, DEFAULT_HIT,
                0, DEFAULT_KW, DEFAULT_LEVEL,
                DEFAULT_DESC, DEFAULT_SHORTDESC,
                DEFAULT_THAC0
        };
    }

    RoomEntity createRoom() {
        std::vector<DoorEntity> doors(1, createDoor());
        return RoomEntity{
                DEFAULT_DESC,
                doors,
                DEFAULT_DESCEXT,
                DEFAULT_KWEXT,
                DEFAULT_NAME,
                DEFAULT_ID
        };
    }

    AreaEntity createArea() {
        std::deque<RoomEntity> rooms{1, createRoom()};
        return AreaEntity{
                DEFAULT_NAME,
                rooms
        };
    }

    DoorEntity createDoor() {
        return DoorEntity{DEFAULT_DESC,
                          DEFAULT_DIRECTION,
                          DEFAULT_KW,
                          DEFAULT_ID};
    }

    ObjectEntity createObject() {
        return ObjectEntity{
                DEFAULT_ATTR,
                DEFAULT_COST,
                DEFAULT_DESCEXT,
                DEFAULT_KWEXT,
                DEFAULT_OTYPEID,
                DEFAULT_ITEMTYPE,
                DEFAULT_KW,
                DEFAULT_DESC,
                DEFAULT_SHORTDESC,
                DEFAULT_WEARFLAGS,
                DEFAULT_WEIGHT
        };
    }
};


/*************************************
 * Area Tests
 *************************************/

TEST_F(EntitiesTests, GetAllRooms) {
    AreaEntity area = createArea();
    EXPECT_EQ(area.getAllRooms().size(), 1);
}


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

TEST_F(EntitiesTests, GetObjectTypeId) {
    ObjectEntity object = createObject();
    EXPECT_EQ(DEFAULT_OTYPEID,
            object.getObjectTypeId());
}

TEST_F(EntitiesTests, GetShortDesc) {
ObjectEntity object = createObject();
EXPECT_EQ(DEFAULT_SHORTDESC,
        object.getShortDesc());
}

TEST_F(EntitiesTests, GetLongDesc) {
ObjectEntity object = createObject();
EXPECT_EQ(DEFAULT_DESC,
        object.getLongDesc());
}

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

TEST_F(EntitiesTests, GetDestRoomIdOf) {
    RoomEntity room = createRoom();
    unsigned int id = room.getDestRoomIdOf(DEFAULT_DIRECTION);
    EXPECT_EQ(id, DEFAULT_ID);
}

TEST_F(EntitiesTests, GetDirs) {
    RoomEntity room = createRoom();
    std::vector<std::string> dirs = room.getDirs();
    EXPECT_EQ(dirs.size(), 1);
}
