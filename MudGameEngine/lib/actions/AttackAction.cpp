#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "actions/AttackAction.h"
#include "gamemanager/GameManager.h"
#include "logging.h"

void AttackAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("AttackAction::execute");

    // get gamestate
    auto &gameState = gameManager.getState();

    // get character who is attacking
    auto characterWhoIsAttacking = characterPerformingAction;

    //--get the room the character is in
    auto characterCurrentRoom =
        gameState.getCharacterLocation(characterWhoIsAttacking);
    if (!characterCurrentRoom) {
        logger->error(
            "Character is not in a room! Suspect incorrect world init");
        // return early, as we are in a bad state - the character is not in a room!
        return;
    }

    //--get list of entities in the room
    auto IDsOfPlayersInRoom =
        gameState.getCharactersInRoom(characterCurrentRoom);
    if (IDsOfPlayersInRoom.empty()) {
        return;
    }
    auto attackingCharactersUniqueId = characterWhoIsAttacking.getEntityId();
    if (actionArguments.empty()) {
        // user did not pass an attack target
        gameManager.sendCharacterMessage(attackingCharactersUniqueId,
                                         "Attack what?");
        logger->info("No Target found");
        return;
    }
    auto nameOfAttackTarget = actionArguments.at(0);
    logger->info("nameOfAttackTarget: " + nameOfAttackTarget);

    // TODO: implement combat component
    // see if my target is in the same room
    for (auto characterID : IDsOfPlayersInRoom) {
        auto currentEntity = gameState.getCharacterFromLUT(characterID);
        if (!currentEntity)
            return;
        auto shortDescOfCurrentPlayer = currentEntity->getShortDesc();
        if (boost::to_lower_copy(shortDescOfCurrentPlayer)
                .compare(boost::to_lower_copy(nameOfAttackTarget)) == 0) {
            // TODO: change this to allow attacking any character
            // TODO: implement proper use of combat states
            // TODO: implement proper combat(in a seperate class)

            // send messages to characters fighting
            auto playerWhoIsBeingAttacking = currentEntity;
            gameManager.sendCharacterMessage(
                characterWhoIsAttacking.getEntityId(),
                "You attack " + playerWhoIsBeingAttacking->getShortDesc() +
                    "and do 1 damage");

            gameManager.sendCharacterMessage(
                playerWhoIsBeingAttacking->getEntityId(),
                "You are attacked by " + characterWhoIsAttacking.getShortDesc() +
                    "and take 1 damage");
            return;
        }
    }

    // if we didnt find the target we tell the player
    logger->info("No Target found");
    gameManager.sendCharacterMessage(attackingCharactersUniqueId,
                                     "Attack failed: could not find " +
                                         nameOfAttackTarget);
}
