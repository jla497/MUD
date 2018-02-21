#include "gamemanager/LutBuilder.h"

namespace mudserver {
namespace gamemanager {

    std::map<roomId, RoomEntity*> LutBuilder::createLUT(std::deque<unique_ptr<RoomEntity>>& rooms) {
    	std::map<roomId, RoomEntity*> mMap{};

    	for (auto& room : rooms ) {
    		mMap.insert(std::make_pair<roomId, RoomEntity*>(room->getId(),room.get()));
    	}

    	return mMap;
    }

    std::map<roomId, NonPlayerCharacter*> LutBuilder::createNpcLUT(std::vector<std::unique_ptr<NonPlayerCharacter>>& npcs){
    	std::map<roomId, NonPlayerCharacter*> mMap{};

    	for (auto& npc : npcs ) {
    		mMap.insert(std::make_pair<roomId, NonPlayerCharacter*>(npc->getNpcTypeId(),npc.get()));
    	}

    	return mMap;
    }

}
}