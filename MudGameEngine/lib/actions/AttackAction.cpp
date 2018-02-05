#include <string>
#include <vector>

#include "actions/AttackAction.h"

void AttackAction::execute() {
	static auto logger = mudserver::logging::getLogger("AttackAction::execute");
    logger->info("Entered AttackAction");

	//get gamestate
	auto& gameState = gameManager.getState();

    // get player who is attacking
    auto playerAttacking = this->characterPerformingAction;
    auto attackTargetNames = this->entitiesBeingActedUpon;

    //--get the room the player is in
    auto roomPlayerIsIn = gameState.getCharacterLocation(&playerAttacking);
    if(roomPlayerIsIn == nullptr){
        logger->error("roomPlayerIsIn does not exist");
    }

    //--get list of entities in the room
    auto IDsOfPlayersInRoom = gameState.getCharactersInRoom(roomPlayerIsIn);
    auto attackingPlayersId = playerAttacking.getEntityId().getId();
    auto attackingPlayersShortDesc = playerAttacking.getShortDesc();

	//see if my target is in the same room


	// for(const auto id: others) {
	// //if it is kill and return 
	// 	//else fail and return
	// }

    //TODO: actually be able to attack entities
    auto nameOfAttackTarget = attackTargetNames.at(0);

        logger->info("calling gameManager.sendCharacterMessage()");
            gameManager.sendCharacterMessage(attackingPlayersId,
                "You try to attack" + nameOfAttackTarget + 
                "but you can't, the feature is unimplemented");
    


    logger->info("Exiting AttackAction");

}
