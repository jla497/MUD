#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "actions/SwapAction.h"
#include "gamemanager/GameManager.h"
#include "logging.h"

void SwapAction::execute() {
    static auto logger = mudserver::logging::getLogger("SwapAction::execute");

    auto &gameState = gameManager.getState();

    // get player who is attacking
    auto swapInitiater = characterPerformingAction;

    //--get the room the player is in
    auto characterCurrentRoom = gameState.getCharacterLocation(swapInitiater);
    if (!characterCurrentRoom) {
        logger->error(
                "Character is not in a room! Suspect incorrect world init");
        return;
    }

    auto IDsOfPlayersInRoom =
            gameState.getCharactersInRoom(characterCurrentRoom);
    if (IDsOfPlayersInRoom.empty()) {
        return;
    }
    auto attackingPlayersUniqueId = swapInitiater.getEntityId();
    if (actionArguments.empty()) {
        gameManager.sendCharacterMessage(
                attackingPlayersUniqueId,
                "Swap with who?");
        logger->info("No Target found");
        return;
    }
    auto nameOfSwapTarget = actionArguments.at(0);
    logger->info("nameOfSwapTarget: " + nameOfSwapTarget);

    for (auto characterID : IDsOfPlayersInRoom) {
        auto currentEntity = gameState.getCharacterFromLUT(characterID);
        if (!currentEntity)
            return;
        auto shortDescOfCurrentPlayer = currentEntity->getShortDesc();
        if (boost::to_lower_copy(shortDescOfCurrentPlayer)
                    .compare(boost::to_lower_copy(nameOfSwapTarget)) == 0) {
            auto swapTarget = currentEntity;
            gameManager.swapCharacters(
                    swapInitiater.getEntityId(),
                    swapTarget->getEntityId());
            gameManager.sendCharacterMessage(
                    swapInitiater.getEntityId(),
                    "You swapped with " + swapTarget->getShortDesc());
            gameManager.sendCharacterMessage(
                    swapTarget->getEntityId(),
                    "You have been swapped with" + swapInitiater.getShortDesc());
            return;
        }
    }

    logger->info("No Target found");
    gameManager.sendCharacterMessage(
            attackingPlayersUniqueId,
            "Swap failed: could not find " +
            nameOfSwapTarget);
}
