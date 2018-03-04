#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "actions/SwapAction.h"
#include "gamemanager/GameManager.h"
#include "logging.h"

SwapAction *SwapAction::clone() { return new SwapAction(*this); }

void SwapAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("SwapAction::execute");
    if (timeRemaining > 0 && timeRemaining < MAX_SWAP_TICKS) {
        logger->debug("swap " + timeRemaining);
        return;
    }

    auto &gameState = gameManager.getState();
    auto swapInitiater = characterPerformingAction;
    auto characterCurrentRoom = gameState.getCharacterLocation(*swapInitiater);
    if (!characterCurrentRoom) {
        logger->error("Character is not in a room! Suspect incorrect world init");
        return;
    }

    auto IDsOfPlayersInRoom = gameState.getCharactersInRoom(characterCurrentRoom);
    if (IDsOfPlayersInRoom.empty()) {
        logger->info("Empty room");
        return;
    }

    auto attackingPlayerId = swapInitiater->getEntityId();
    if (actionArguments.empty()) {
        gameManager.sendCharacterMessage(
                attackingPlayerId,
                "Swap with who?");
        logger->info("No Target found");
        return;
    }

    auto nameOfSwapTarget = actionArguments.at(0);
    logger->info("nameOfSwapTarget: " + nameOfSwapTarget);
    for (auto characterID : IDsOfPlayersInRoom) {
        auto currentEntity = gameState.getCharacterFromLUT(characterID);
        if (!currentEntity) {
            return;
        }
        auto shortDescOfCurrentPlayer = currentEntity->getShortDesc();
//        if (boost::to_lower_copy(shortDescOfCurrentPlayer)
//                    .compare(boost::to_lower_copy(nameOfSwapTarget)) == 0) {
        if (boost::to_lower_copy(shortDescOfCurrentPlayer) == boost::to_lower_copy(nameOfSwapTarget)) {
            auto swapTarget = currentEntity;
            gameManager.swapCharacters(
                    swapInitiater->getEntityId(),
                    swapTarget->getEntityId());
            if (timeRemaining == 0) {
                timeRemaining = MAX_SWAP_TICKS;
                gameManager.sendCharacterMessage(
                        swapInitiater->getEntityId(),
                        "You have returned to your original body " + swapInitiater->getShortDesc());
                gameManager.sendCharacterMessage(
                        swapTarget->getEntityId(),
                        "You have returned to your original body " + swapTarget->getShortDesc());
            }
            else {
                gameManager.sendCharacterMessage(
                        swapTarget->getEntityId(),
                        "You swapped with " + swapTarget->getShortDesc());
                gameManager.sendCharacterMessage(
                        swapInitiater->getEntityId(),
                        "You have been swapped with" + swapInitiater->getShortDesc());
            }
            return;
        }
    }

    logger->info("No Target found");
    gameManager.sendCharacterMessage(
            attackingPlayerId,
            "Swap failed: could not find " + nameOfSwapTarget);
}
