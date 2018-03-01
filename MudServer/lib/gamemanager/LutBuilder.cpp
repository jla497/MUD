
#include "gamemanager/LutBuilder.h"

namespace mudserver {
namespace gamemanager {

std::unordered_map<roomId, RoomEntity>
LutBuilder::createLUT(std::deque<RoomEntity> &rooms) {
    std::unordered_map<roomId, RoomEntity> map;
    for (auto &room : rooms) {
        map[room.getId()] = room;
    }
    return map;
}

std::map<Id, NonPlayerCharacter> LutBuilder::createNpcLUT(
    std::vector<std::unique_ptr<NonPlayerCharacter>> &npcs) {
    std::map<Id, NonPlayerCharacter> map;
    for (auto &npc : npcs) {
        auto npcPtr = npc.get();
        map[npc->getNpcTypeId()] = *npcPtr;
    }
    return map;
}
} // namespace gamemanager
} // namespace mudserver
