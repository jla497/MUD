#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "actions/AttackAction.h"
#include "logging.h"
#include "gamemanager/GameManager.h"


void AttackAction::execute() {
	static auto logger = mudserver::logging::getLogger("AttackAction::execute");
    logger->info("Entered AttackAction");

	//get gamestate
	auto& gameState = gameManager.getState();

	// get player who is attacking
    auto playerWhoIsAttacking = characterPerformingAction;

    //--get the room the player is in
    auto characterCurrentRoom =
        gameState.getCharacterLocation(&playerWhoIsAttacking);
    if (!characterCurrentRoom) {
        logger->error(
            "Character is not in a room! Suspect incorrect world init");
        // return early, as we are in a bad state - the player is not in a room!
        return;
    }

    //--get list of entities in the room
    auto IDsOfPlayersInRoom = gameState.getCharactersInRoom(characterCurrentRoom);
    if(IDsOfPlayersInRoom.empty()){
    	return;
    }
    auto attackingPlayersUniqueId = playerWhoIsAttacking.getEntityId();
    if(actionArguments.empty()){
    	//user did not pass an attack target
    	gameManager.sendCharacterMessage(attackingPlayersUniqueId,
    	"Attack what?");
    	logger->info("No Target found");
    	return;
    }
    auto nameOfAttackTarget = actionArguments.at(0);
   	logger->info("Name of attacker: " + nameOfAttackTarget);


    //TODO: make changes so that the player can attack any arbritrary entity.
	//see if my target is in the same room
    for (auto characterID : IDsOfPlayersInRoom) {
    	auto currentEntity = gameState.getCharacterFromLUT(characterID);
    	if(!currentEntity)
    		return;
    	//auto keyWordsOfCurrentEntity = currentEntity->getKeywords();
    	auto shortDescOfCurrentPlayer = currentEntity->getShortDesc();
    	//for(auto keyword : keyWordsOfCurrentEntity){
    		//if(boost::to_upper_copy(keyword).compare(boost::to_upper_copy(nameOfAttackTarget)) == 0){
    		if(boost::to_upper_copy(shortDescOfCurrentPlayer).compare(boost::to_upper_copy(nameOfAttackTarget)) == 0){
    			//we found the entity the player wants to fight.
    			//TODO: change this to allow attacking any entity
    			//startPVPAttack(playerWhoIsAttacking,currentEntity,gameManager);

    			//TODO: implement proper use of combat states
				//TODO: implement proper combat(in a seperate class)
				//send messages to characters fighting
				auto playerWhoIsBeingAttacking = currentEntity;
				gameManager.sendCharacterMessage(playerWhoIsAttacking.getEntityId(),
			       "You attack" + playerWhoIsBeingAttacking->getShortDesc() + "and do 0.00000000000001 damage");

				gameManager.sendCharacterMessage(playerWhoIsBeingAttacking->getEntityId(),
			       "You are attacked by " + playerWhoIsAttacking.getShortDesc() + "and take 0.00000000000001 damage");
    			return;
    		}
    	}
   // }
  
	//if we didnt find the target we tell the player
	logger->info("No Target found");
    gameManager.sendCharacterMessage(attackingPlayersUniqueId,
    	"Attack failed: could not find " + nameOfAttackTarget);
    logger->info("Exiting AttackAction");
}
