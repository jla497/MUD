#include "CombatSimulation.h"

namespace CombatSimulation {

	static void resolveCombatRound(CharacterEntity& characterWhoIsAttacking,
		CharacterEntity&  characterWhoIsBeingAttacked,
		GameManager& gameManager){

		CombatComponent* attackingCharactersCombatComponent = characterWhoIsAttacking.getCombatComponent();
		CombatComponent* attackedCharactersCombatComponent = characterWhoIsBeingAttacked.getCombatComponent();

		gameManager.sendCharacterMessage(characterWhoIsAttacking.getEntityId(),"Resolving combat round");
		gameManager.sendCharacterMessage(characterWhoIsBeingAttacked.getEntityId(),"Resolving combat round");	



        //inside Combat
        //playerWhoIsAttacking.getCombatComponent() then do some calculations and change game state + send player messages

     	// TODO: implement proper use of combat states
        // TODO: implement proper combat(in a seperate class)


        //set combat states of fighters to fighting
		attackingCharactersCombatComponent->engageCombatState();
		attackedCharactersCombatComponent->engageCombatState();
		
        //calc damage to deal(hard coded for now)
        /*
        int damageToDeal calcDamage(attackingCharactersCombatComponent->getDamageRoll(),
        attackedCharactersCombatComponent->getHitRoll());
        */
		int damageToDeal = 5;

        //dead damage and end combat if the attacked dies
		bool enemyWasKilled = attackedCharactersCombatComponent->damage(5);
		if(enemyWasKilled){
			attackingCharactersCombatComponent->endCombatState();
			attackedCharactersCombatComponent->endCombatState();
		}
	}
}