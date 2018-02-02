#include "LutBuilder.h"

namespace mudserver {
namespace gamemanager {
    std::map<int, RoomEntity&> LutBuilder::createLUT(std::vector<std::unique_ptr<RoomEntity>> rooms) {
    	std::map<int, RoomEntity&> mMap{};
    	for (const auto& room : rooms ) {
    		mMap.insert(std::make_pair<int,RoomEntity&>(std::rand(),*room));
    	}

    	return mMap;
    }

}
}