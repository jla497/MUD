#include "CombatSimulation.h"


int CombatSimulation::calcRoundDamage(Roll damageRoll, Roll hitRoll){
	return 5;
}





void CombatSimulation::resolveCombatRound(CharacterEntity& characterWhoIsAttacking,
	CharacterEntity&  characterWhoIsBeingAttacked,
	GameManager& gameManager){

	//get fighters combat components
	CombatComponent* attackingCharactersCombatComponent = characterWhoIsAttacking.getCombatComponent();
	CombatComponent* attackedCharactersCombatComponent = characterWhoIsBeingAttacked.getCombatComponent();


	gameManager.sendCharacterMessage(characterWhoIsAttacking.getEntityId(),"Starting combat round");
	gameManager.sendCharacterMessage(characterWhoIsBeingAttacked.getEntityId(),"Starting combat round");

    //set combat states of fighters to fighting
	attackingCharactersCombatComponent->engageCombatState();
	attackedCharactersCombatComponent->engageCombatState();


    //calc damage to deal(hard coded for now)
    
  	//TODO: use CombatAbilities rather than just raw roll values  
  	//A CombatAbility should encapsulate the damage dealth along site any effects it might apply
  	//(ex a fireball might apply a burning effect on the target)
    int damageAmount = calcRoundDamage(attackingCharactersCombatComponent->getDamageRoll(),
    	(attackedCharactersCombatComponent->getHitRoll()));
    
	//int damageAmount = 5;

    //deal damage 
	bool enemyWasKilled = attackedCharactersCombatComponent->damage(5);	

    // send messages to characters fighting
	gameManager.sendCharacterMessage(
		characterWhoIsAttacking.getEntityId(),
		"You attack " + characterWhoIsBeingAttacked.getShortDesc() +
		" and do " + std::to_string(damageAmount) + " damage");

	gameManager.sendCharacterMessage(
		characterWhoIsBeingAttacked.getEntityId(),
		"You are attacked by " + characterWhoIsAttacking.getShortDesc() +
		" and take " + std::to_string(damageAmount) + " damage");



	//exit combat state and remove Character from world if the attacked dies
	if(enemyWasKilled){
		attackingCharactersCombatComponent->endCombatState();
		attackedCharactersCombatComponent->endCombatState();

	gameManager.sendCharacterMessage(
		characterWhoIsAttacking.getEntityId(),
		"You killed " + characterWhoIsBeingAttacked.getShortDesc());
	gameManager.sendCharacterMessage(
		characterWhoIsBeingAttacked.getEntityId(),
		"You are were killed by " + characterWhoIsAttacking.getShortDesc());


		//calculate rewards and give them to the attacker
		int goldToGive = 55;
		int expToGive = 33;




		//remove killed character from game state
		//GameManager.getGameState().killCharacter(characterWhoIsBeingAttacked.getEntityId());

		//remove from play

		//if the character is controlled by a player notify them

	}

	gameManager.sendCharacterMessage(characterWhoIsAttacking.getEntityId(),"Ending combat round");
	gameManager.sendCharacterMessage(characterWhoIsBeingAttacked.getEntityId(),"Ending combat round");	
}


//TODO: change this to a gameState function
// void CharacterEntity::die(GameManager& gameManager){
//     //remove from play
//     //if the character is controlled by a player notify them
//     //gameManager.getGameState().removeCharacterByUniqueId(getEntityId());


// }



