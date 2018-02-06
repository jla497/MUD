#include "gamemanager/LutBuilder.h"

namespace mudserver {
namespace gamemanager {
    std::unordered_map<roomId, RoomEntity*> LutBuilder::createLUT(std::vector<std::unique_ptr<RoomEntity>>& rooms) {
    	std::unordered_map<roomId, RoomEntity*> mMap{};
    	std::cout<<"in lutBuilder..."<<std::endl;
    	for (auto& room : rooms ) {
    		auto rid = room->getId();
    		auto roomPtr = room.get();
    		std::cout<<"room id: "<<rid<<" "<<"roomPtr id: "<<roomPtr->getId()<<std::endl;
    		mMap.insert(std::make_pair<roomId, RoomEntity*>(room->getId(),room.get()));
    	}

    	return mMap;
    }

}
}