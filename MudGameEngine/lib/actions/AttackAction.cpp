#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "actions/AttackAction.h"
#include "gamemanager/GameManager.h"
#include "logging.h"
AttackAction *AttackAction::clone() { return new AttackAction(*this); }

void AttackAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("AttackAction::execute");

    // get gamestate
    auto &gameState = gameManager.getState();

    // get player who is attacking
    auto playerWhoIsAttacking = characterPerformingAction;

    //--get the room the player is in
    auto characterCurrentRoom =
        gameState.getCharacterLocation(playerWhoIsAttacking);
    if (!characterCurrentRoom) {
        logger->error(
            "Character is not in a room! Suspect incorrect world init");
        // return early, as we are in a bad state - the player is not in a room!
        return;
    }

    //--get list of entities in the room
    auto IDsOfPlayersInRoom =
        gameState.getCharactersInRoom(characterCurrentRoom);
    if (IDsOfPlayersInRoom.empty()) {
        return;
    }
    auto attackingPlayersUniqueId = playerWhoIsAttacking.getEntityId();
    if (actionArguments.empty()) {
        // user did not pass an attack target
        gameManager.sendCharacterMessage(attackingPlayersUniqueId,
                                         "Attack what?");
        logger->info("No Target found");
        return;
    }
    auto nameOfAttackTarget = actionArguments.at(0);
    logger->info("nameOfAttackTarget: " + nameOfAttackTarget);

    // TODO: make changes so that the player can attack any arbritrary entity.
    // see if my target is in the same room
    for (auto characterID : IDsOfPlayersInRoom) {
        auto currentEntity = gameState.getCharacterFromLUT(characterID);
        if (!currentEntity)
            return;
        auto shortDescOfCurrentPlayer = currentEntity->getShortDesc();
        if (boost::to_lower_copy(shortDescOfCurrentPlayer)
                .compare(boost::to_lower_copy(nameOfAttackTarget)) == 0) {
            // TODO: change this to allow attacking any entity rather than just
            // players
            // TODO: implement proper use of combat states
            // TODO: implement proper combat(in a seperate class)

            // send messages to characters fighting
            auto playerWhoIsBeingAttacking = currentEntity;
            gameManager.sendCharacterMessage(
                playerWhoIsAttacking.getEntityId(),
                "You attack " + playerWhoIsBeingAttacking->getShortDesc() +
                    "and do 1 damage");

            gameManager.sendCharacterMessage(
                playerWhoIsBeingAttacking->getEntityId(),
                "You are attacked by " + playerWhoIsAttacking.getShortDesc() +
                    "and take 1 damage");
            return;
        }
    }

    // if we didnt find the target we tell the player
    logger->info("No Target found");
    gameManager.sendCharacterMessage(attackingPlayersUniqueId,
                                     "Attack failed: could not find " +
                                         nameOfAttackTarget);
}
