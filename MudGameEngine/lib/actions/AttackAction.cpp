#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "actions/AttackAction.h"
#include "gamemanager/GameManager.h"
#include "logging.h"
#include "CombatSimulation.h"
#include "entities/CharacterEntity.h"

AttackAction *AttackAction::clone() { return new AttackAction(*this); }

class CombatComponent;
class CharacterEntity;
void AttackAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("AttackAction::execute");

    // get gamestate
    auto &gameState = gameManager.getState();

    // get player who is attacking
    auto playerWhoIsAttacking = characterPerformingAction;

    //--get the room the player is in
    auto characterCurrentRoom =
        gameState.getCharacterLocation(*playerWhoIsAttacking);
    if (!characterCurrentRoom) {
        logger->error(
            "Character is not in a room! Suspect incorrect world init");
        // return early, as we are in a bad state - the player is not in a room!
        return;
    }

    //--get ids of characters in the attackers room
    auto IDsOfPlayersInRoom =
        gameState.getCharactersInRoom(characterCurrentRoom);
    if (IDsOfPlayersInRoom.empty()) {
        return;
    }
    auto attackingPlayersUniqueId = playerWhoIsAttacking->getEntityId();
    if (actionArguments.empty()) {
        // user did not pass an attack target
        gameManager.sendCharacterMessage(attackingPlayersUniqueId,
                                         "Attack what?");
        logger->info("No Target found");
        return;
    }
    auto nameOfAttackTarget = actionArguments.at(0);
    logger->info("nameOfAttackTarget: " + nameOfAttackTarget);


    // see if the target is in the same room as the attacker
    for (auto characterID : IDsOfPlayersInRoom) {
        auto currentEntity = gameState.getCharacterFromLUT(characterID);
        if (!currentEntity)
            return;
        auto shortDescOfCurrentPlayer = currentEntity->getShortDesc();
        if (boost::to_lower_copy(shortDescOfCurrentPlayer) ==
            boost::to_lower_copy(nameOfAttackTarget)) {


            playerWhoIsAttacking->getCombatComponent()->prepareToAttack();
            //calculate and apply attack effects
            CombatSimulation::resolveCombatRound(*playerWhoIsAttacking, *currentEntity,gameManager);
            return;
        }
    }

    // if we didnt find the target we tell the player
    logger->info("No Target found");
    gameManager.sendCharacterMessage(attackingPlayersUniqueId,
                                     "Attack failed: could not find " +
                                         nameOfAttackTarget);
}
