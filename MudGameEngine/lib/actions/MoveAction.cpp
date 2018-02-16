#include "actions/MoveAction.h"
#include "logging.h"

std::vector<std::string> MoveAction::moveLookup = {"north","south","east","west"};

void MoveAction::execute() {
    static auto logger = mudserver::logging::getLogger("Action::MoveAction");

    logger->info("MoveAction...");
    std::string userinfo(
        "userid: " +
        std::to_string(characterPerformingAction.getEntityId().getId()));
    logger->info(userinfo);

    auto& gameState = gameManager.getState();
	RoomEntity* room = gameState.getCharacterLocation(characterPerformingAction);

    if (!room) {
        logger->error("Character not found in any room...");
        return;
	}
    std::string roomInfo("roomid: " + std::to_string(room->getId()));
    logger->info(roomInfo);
    
    if(actionArguments.empty()) {
        logger->error("Not a valid move command...");
        gameManager.sendCharacterMessage(characterPerformingAction.getEntityId(),
                                         "Not a valid move command...");
        return;
    }

    auto cmd = actionArguments[0];

	boost::algorithm::to_lower(cmd);

	auto direction = std::find(moveLookup.begin(), moveLookup.end(), cmd);

	if(direction == moveLookup.end()) {
        logger->error("not a valid direction...");
        return;
	}else {
		
		//get next room id from current room

		auto nextRoomId = room->getDestRoomIdOf(*direction);

		//not a valid direction	
		if(nextRoomId == -1) {
			return;
		}

        logger->info("got nextRoomId...");
        //get nextroom
		auto nextRoom = gameState.getRoomFromLUT(nextRoomId);
		//Room with nextRoomId does not exist
        if (!nextRoom) {
            logger->error("nextRoom is null...");
            return;
		}

        std::string nextRoomIdStr("next room id: " +
                                  std::to_string(nextRoom->getId()));
        logger->info(nextRoomIdStr);
        //move the playerCharacter from the current room to the next room
		auto characterId = characterPerformingAction.getEntityId().getId();
		
		room->removeEntity(characterId);

		nextRoom->addEntity(characterId);

		auto mCharacterPtr = &characterPerformingAction;
		gameState.addCharacterRoomRelationToLUT(mCharacterPtr->getEntityId(), nextRoom->getId());
        logger->info("MoveAction complete...");
        return;
	}


	

}
