#include "gamemanager/LutBuilder.h"

namespace mudserver {
namespace gamemanager {

    std::map<roomId, RoomEntity*> LutBuilder::createLUT(std::deque<unique_ptr<RoomEntity>>& rooms) {
    	std::map<roomId, RoomEntity*> mMap{};

    	for (auto& room : rooms ) {
    		auto rid = room->getId();
    		mMap.insert(std::make_pair<roomId, RoomEntity*>(room->getId(),room.get()));
    	}

    	return mMap;
    }

}
}