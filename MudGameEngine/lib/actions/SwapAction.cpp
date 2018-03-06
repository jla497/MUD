#include <boost/algorithm/string.hpp>
#include "actions/SwapAction.h"

SwapAction *SwapAction::clone() { return new SwapAction(*this); }

void SwapAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("SwapAction::execute");

    // Swap in progress, wait until time is up
    if (timeRemaining > 0) {
        return;
    }

    // Swap is done, revert swap made
    else if (timeRemaining == 0) {
        gameManager.swapCharacters(casterId, targetId);
        gameManager.sendCharacterMessage(
                casterId,
                "You have returned to your original body");
        gameManager.sendCharacterMessage(
                targetId,
                "You have returned to your original body");
        return;
    }

    // Timer hasn't been set yet, start the initial swap
    auto &gameState = gameManager.getState();
    auto swapInitiater = characterPerformingAction;
    auto characterCurrentRoom = gameState.getCharacterLocation(*swapInitiater);
    if (!characterCurrentRoom) {
        logger->error("Character is not in a room! Suspect incorrect world init");
        return;
    }
    auto IDsOfPlayersInRoom = gameState.getCharactersInRoom(characterCurrentRoom);
    if (IDsOfPlayersInRoom.empty()) {
        logger->debug("Empty room");
        return;
    }
    auto swappingPlayerId = swapInitiater->getEntityId();
    if (actionArguments.empty()) {
        gameManager.sendCharacterMessage(
                swappingPlayerId,
                "Specify swap target?");
        logger->debug("No Target found");
        return;
    }
    auto nameOfSwapTarget = actionArguments.at(0);
    for (auto characterID : IDsOfPlayersInRoom) {
        auto currentEntity = gameState.getCharacterFromLUT(characterID);
        if (!currentEntity) {
            return;
        }
        auto shortDescOfCurrentPlayer = currentEntity->getShortDesc();
        if (boost::to_lower_copy(shortDescOfCurrentPlayer) == boost::to_lower_copy(nameOfSwapTarget)) {
            auto swapTarget = currentEntity;
            casterId = swapInitiater->getEntityId();
            targetId = swapTarget->getEntityId();
            timeRemaining = MAX_SWAP_TICKS;
            gameManager.sendCharacterMessage(
                    casterId,
                    "You swapped with " + swapTarget->getShortDesc());
            gameManager.sendCharacterMessage(
                    targetId,
                    "You have been swapped with" + swapInitiater->getShortDesc());
            gameManager.swapCharacters(casterId, targetId);
            return;
        }
    }

    logger->debug("No Target found");
    gameManager.sendCharacterMessage(
            swappingPlayerId,
            "Swap failed: could not find " + nameOfSwapTarget);
}
