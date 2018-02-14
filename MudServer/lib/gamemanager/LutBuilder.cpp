
#include "gamemanager/LutBuilder.h"

namespace mudserver {
namespace gamemanager {

std::unordered_map<roomId, RoomEntity> LutBuilder::createLUT(std::deque<RoomEntity>& rooms) {
	std::unordered_map<roomId, RoomEntity> map;
	for (auto &room : rooms) {
		map[room.getId()] = room;
	}
	return map;
}
}
}
