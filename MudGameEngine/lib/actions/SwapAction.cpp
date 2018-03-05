#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "actions/SwapAction.h"
#include "gamemanager/GameManager.h"
#include "logging.h"

SwapAction *SwapAction::clone() { return new SwapAction(*this); }

void SwapAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("SwapAction::execute");
    logger->debug("tick");
    if (timeRemaining > 0) {
        return;
    }
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

    // Timer hasn't been set yet, do initial swap

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

    auto swappingPlayerId = swapInitiater->getEntityId();
    if (actionArguments.empty()) {
        gameManager.sendCharacterMessage(
                swappingPlayerId,
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

    logger->info("No Target found");
    gameManager.sendCharacterMessage(
            swappingPlayerId,
            "Swap failed: could not find " + nameOfSwapTarget);
}
