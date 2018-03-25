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

public:
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

    RoomEntity createRoom() {
        std::vector<std::string> desc{};
        std::vector<DoorEntity> doors{};
        std::vector<std::string> descExt{};
        std::vector<std::string> keywordsExt{};
        std::string name = "testRoom";
        unsigned int roomId = 1;
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
        std::vector<std::string> desc{};
        std::vector<std::string> keywords{};
        return DoorEntity{desc, "direction", keywords, 0};
    }

    ObjectEntity createObject() {
        std::vector<std::string> attributes{};
        unsigned int cost = 1;
        unsigned int objectTypeId = 1;
        std::string itemType = "none";
        std::vector<std::string> descExtra{};
        std::vector<std::string> keywordsExtra{};
        std::vector<std::string> keywords{};
        std::vector<std::string> longDesc{};
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
                keywords,
                longDesc,
                shortDesc,
                wearFlags,
                weight
        };
    }


};

TEST_F(EntitiesTests, CreateArea) {

}
