#include "actions/MoveAction.h"

std::vector<std::string> MoveAction::moveLookup = {"north","south","east","west"};

void MoveAction::execute() {
	std::cout<<"in execute..."<<std::endl;
	auto& gameState = gameManager.getState();
	std::cout<<"character id: "<<characterPerformingAction.getEntityId().getId()<<std::endl;
	auto room = gameState.getCharacterLocation(characterPerformingAction);
	
	if (room == NULL) {
		std::cout<<"character not found in any room..."<<std::endl;
	}

	std::cout<<"room id is : "<<room->getId()<<std::endl;

	auto cmd = entitiesBeingActedUpon[0];

	boost::algorithm::to_lower(cmd);

	auto direction = std::find(moveLookup.begin(), moveLookup.end(), cmd);

	if(direction == moveLookup.end()) {
		std::cout<<"not a valid direction..."<<std::endl;
		return;
	}else {
		std::cout<<"getting next room id..."<<std::endl;
		
		//get next room id from current room

		auto nextRoomId = room->getDestRoomIdOf(*direction);

		std::cout<<"got nextRoomId..."<<std::endl;
		//get nextroom
		auto nextRoom = gameState.getRoomFromLUT(nextRoomId);

		std::cout<<"got nextRoom..."<<std::endl;
		//move the playerCharacter from the current room to the next room
		auto characterId = characterPerformingAction.getEntityId().getId();
		std::cout<<"got chararcterID..."<<std::endl;
		room->removeEntity(characterId);

		nextRoom->addEntity(characterId);
		return;
	}


	

}
