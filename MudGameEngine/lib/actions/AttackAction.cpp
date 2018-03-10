#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "CombatSimulation.h"
#include "actions/AttackAction.h"
#include "entities/CharacterEntity.h"
#include "gamemanager/GameManager.h"
#include "logging.h"

AttackAction *AttackAction::clone() { return new AttackAction(*this); }

class CombatComponent;
class CharacterEntity;
void AttackAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("AttackAction::execute");

    // get gamestate
    auto &gameState = gameManager.getState();

    // get character who is attacking
    auto characterWhoIsAttacking = characterPerformingAction;

    //--get the room the character is in
    auto characterCurrentRoom =
        gameState.getCharacterLocation(*characterWhoIsAttacking);
    if (!characterCurrentRoom) {
        logger->error(
            "Character is not in a room! Suspect incorrect world init");
        // return early, as we are in a bad state - the character is not in a room!
        return;
    }

    //--get ids of characters in the attackers room
    auto IDsOfCharactersInRoom =
        gameState.getCharactersInRoom(characterCurrentRoom);
    if (IDsOfCharactersInRoom.empty()) {
        return;
    }
    auto attackingCharactersUniqueId = characterWhoIsAttacking->getEntityId();
    if (actionArguments.empty()) {
        // user did not pass an attack target
        gameManager.sendCharacterMessage(attackingCharactersUniqueId,
                                         "Attack what?");
        logger->info("No Target found");
        return;
    }
    auto nameOfAttackTarget = boost::join(actionArguments, " ");
    logger->info("nameOfAttackTarget: " + nameOfAttackTarget);

    // see if the target is in the same room as the attacker
    for (auto characterID : IDsOfCharactersInRoom) {
        auto currentEntity = gameState.getCharacterFromLUT(characterID);
        if (!currentEntity)
            return;
        auto shortDescOfCurrentCharacter = currentEntity->getShortDesc();
        if (boost::to_lower_copy(shortDescOfCurrentCharacter) ==
            boost::to_lower_copy(nameOfAttackTarget)) {

            // calculate and apply attack effects
            characterWhoIsAttacking->getCombatComponent()->prepareToAttack();
            CombatSimulation::resolveCombatRound(*characterWhoIsAttacking,
                                                 *currentEntity, gameManager);

                //log hp of target
                logger->info(nameOfAttackTarget + ": " + 
                    currentEntity->getCombatComponent()->getHealthDescription());
                //display the targets hp to the attacker 
                gameManager.sendCharacterMessage(attackingCharactersUniqueId,
                    nameOfAttackTarget + ": " + 
                    currentEntity->getCombatComponent()->getHealthDescription());
                
            return;
        }
    }

    // if we didnt find the target tell the attacker
    logger->info("No Target found");
    gameManager.sendCharacterMessage(attackingCharactersUniqueId    ,
                                     "Attack failed: could not find " +
                                         nameOfAttackTarget);
}
