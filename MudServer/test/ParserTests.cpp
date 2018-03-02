#include "reset/Reset.h"
#include "YamlParser.h"
#include "entities/Entity.h"
#include "entities/RoomEntity.h"
#include "gamemanager/LutBuilder.h"
#include <gtest/gtest.h>

class ParserTests : public testing::Test {
    void SetUp() override {
        rooms.push_back({
            {"desc1"},          // desc
            {},                 // doors
            {"extended desc1"}, // extended desc
            {"keyword1"},       // extended keywords
            "room1",            // name
            1                   // id
        });
        parser.loadYamlFile("MudGameEngine/lib/dataFiles/detailed_mgoose.yml");
    }

    void TearDown() override {}

  public:
    std::vector<RoomEntity> rooms{};
    YamlParser parser{};
};

TEST_F(ParserTests, TestGetAllNPCS) { auto npcs = parser.getAllNPCS(); }

TEST_F(ParserTests, TestGetAllObjects) {
    auto objects = parser.getAllObjects();
}

TEST_F(ParserTests, TestGetAllResets) { auto resets = parser.getAllResets(); }

TEST_F(ParserTests, TestParseArea) { auto area = parser.getArea(); }

TEST_F(ParserTests, TestLutBuilder) {
    auto area = parser.getArea();
    std::deque<RoomEntity> &rooms = area.getAllRooms();
    mudserver::gamemanager::LutBuilder lutBuilder{};
    auto mMap = lutBuilder.createLUT(rooms);

    unsigned int roomNum = 2900;
    auto room = mMap[roomNum];
    EXPECT_EQ(roomNum, room.getId());

    auto descriptions = room.getDesc();
}
