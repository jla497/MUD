#include <string>
#include <vector>

#include "actions/AttackAction.h"

void AttackAction::execute() {
	//get gamestate
	auto& gameState = gameManager.getState();

	//get my character
	// auto myChar = gameState.getCharacter(entityPerformingAction);

	// //get my room
	// auto room = gameState.getCharacterLocation(myChar);
	// //see if my target is in the same room
	// auto others = gamestate.getCharactersInRoom(room);

	// for(const auto id: others) {
	// //if it is kill and return 
	// 	//else fail and return

	// }
}
