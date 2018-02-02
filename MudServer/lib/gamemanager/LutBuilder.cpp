#include "LutBuilder.h"

namespace mudserver {
namespace gamemanager {
    std::map<UniqueId, RoomEntity&> LutBuilder::createLUT(std::vector<std::unique_ptr<RoomEntity>> rooms) {
    	std::map<UniqueId, RoomEntity&> mMap{};
    	for (const auto& room : rooms ) {
    		mMap.insert(std::make_pair<room->getEntityId(),RoomEntity&>(std::rand(),*room));
    	}

    	return mMap;
    }

}
}