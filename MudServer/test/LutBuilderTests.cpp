#include <gtest/gtest.h>
#include "RoomEntity.h"
#include "YamlParser.h"
#include "gamemanager/LutBuilder.h"


class LutBuilderTests : public testing::Test {
    virtual void SetUp() {
    	YamlParser parser{};
    	parser.loadYamlFile("detailed_mongoose.yml");
    }

    virtual void TearDown() {

    }

    std::vector<std::unique_ptr<RoomEntity>> rooms;
};

TEST_F(LutBuilderTests, testLUTBuild) {
    	// auto& rooms = area.getAllRooms();
    	// auto LutBuilder lutBuilder{};
    	// auto mMap = lutBuilder.createLUT(rooms);

}  // namespace mudserver