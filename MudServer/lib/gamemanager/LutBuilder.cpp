#include "gamemanager/LutBuilder.h"

namespace mudserver {
namespace gamemanager {
    std::map<roomId, RoomEntity*> LutBuilder::createLUT(std::vector<std::unique_ptr<RoomEntity>>& rooms) {
    	std::map<roomId, RoomEntity*> mMap{};
    	for (auto& room : rooms ) {
    		mMap.insert(std::make_pair<roomId, RoomEntity*>(room->getId(),room.get()));
    	}

    	return mMap;
    }

}
}