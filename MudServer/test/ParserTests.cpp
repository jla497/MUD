#include <gtest/gtest.h>
#include "RoomEntity.h"
#include "NPCEntity.h"
#include "YamlParser.h"
#include "Entity.h"


std::string filename {};

class ParserTests : public testing::Test {
  virtual void SetUp() {
    std::vector<std::string> desc {};
    desc.push_back("desc1");

    std::vector<std::string> descExt {};
    descExt.push_back("extended desc1");

    std::vector<std::unique_ptr<DoorEntity>> doors {};

    std::vector<std::string> keywordsExt {};

    keywordsExt.push_back("keyword1");

    std::string name("room1");

    unsigned int roomId = 1;
    auto room = std::make_unique<RoomEntity>(desc, std::move(doors), descExt, keywordsExt, name, roomId);
    rooms.push_back(std::move(room));
    parser.loadYamlFile(filename);
  }

  virtual void TearDown() {

  }
public:
  std::vector<std::unique_ptr<RoomEntity>> rooms {};
  YamlParser parser{};
};

TEST_F(ParserTests, TestGetAllNPCS) {
  auto npcs = parser.getAllNPCS();
}

TEST_F(ParserTests, TestGetAllObjects) {
  auto objects = parser.getAllObjects();
}

TEST_F(ParserTests, TestParseArea) {
  auto area = parser.getArea();
  EXPECT_EQ("MotherGoose", area->getName());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

   filename = argv[1];

   if (filename.empty()) {
     std::cout << "missing parser test data file name" << std::endl;
     return -1;
   }
  return RUN_ALL_TESTS();
}
