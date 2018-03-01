
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
    std::vector<NonPlayerCharacter> &npcs) {
    std::map<Id, NonPlayerCharacter> map;
    for (auto &npc : npcs) {
        map[npc.getNpcTypeId()] = npc;
    }
    return map;
}
} // namespace gamemanager
} // namespace mudserver
