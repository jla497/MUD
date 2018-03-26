#include "actions/TakeAction.h"
#include "entities/RoomEntity.h"
#include "logging.h"

#include <boost/algorithm/string/join.hpp>
#include <boost/optional.hpp>

using boost::algorithm::join;

std::unique_ptr<Action> TakeAction::clone() const {
    return std::make_unique<TakeAction>(*this);
}
// TakeAction *TakeAction::clone() { return new TakeAction(*this); }

void TakeAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("Action::TakeAction");

    auto &gameState = gameManager.getState();

    auto characterCurrentRoom =
        gameState.getCharacterLocation(*characterPerformingAction);
    if (!characterCurrentRoom) {
        logger->error(
            "Character is not in a room! Suspect incorrect world init");
        // return early, as we are in a bad state - the player is not in a room!
        return;
    }

    if (!actionArguments.empty()) {
        auto nameOfObject = join(actionArguments, " ");
        logger->debug("Trying to move " + nameOfObject + " to inventory");

        auto objectToTake =
            characterCurrentRoom->takeObjectByName(nameOfObject);

        if (objectToTake != boost::none) {
            gameManager.sendCharacterMessage(
                characterPerformingAction->getEntityId(),
                nameOfObject + " taken from room");

            characterPerformingAction->addObject(*objectToTake);
            characterCurrentRoom->removeObject(objectToTake);
        } else {
            gameManager.sendCharacterMessage(
                characterPerformingAction->getEntityId(),
                nameOfObject + " not found in room");
        }

    } else {
        // error that you need to try and take something
        gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(),
            "Please type 'take <object's short description (before colon)>'");
    }
}
