
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

std::map<Id, CharacterEntity> LutBuilder::createNpcLUT(
    std::vector<CharacterEntity> &npcs) {
    std::map<Id, CharacterEntity> map;
    for (auto &npc : npcs) {
        map[npc.getTypeId()] = npc;
    }
    return map;
}
} // namespace gamemanager
} // namespace mudserver
