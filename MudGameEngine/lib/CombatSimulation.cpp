#include "CombatSimulation.h"

namespace CombatSimulation{

     static void resolveCombatRound(CharacterEntity& characterWhoIsAttacking,
    	CharacterEntity&  characterWhoIsBeingAttacked,
    	GameManager& gameManager){

             gameManager.sendCharacterMessage(
                characterWhoIsAttacking.getEntityId(),"Resolving combat round");

            gameManager.sendCharacterMessage(
                characterWhoIsBeingAttacked.getEntityId(),"Resolving combat round");    	

     }
}