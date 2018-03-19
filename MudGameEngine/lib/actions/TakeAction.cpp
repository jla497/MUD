#include "actions/TakeAction.h"
#include "entities/RoomEntity.h"
#include "logging.h"

#include <boost/optional.hpp>
#include <boost/algorithm/string/join.hpp>

using boost::algorithm::join;

std::unique_ptr<Action> TakeAction::clone() const { 
	return std::make_unique<TakeAction>(*this); }
// TakeAction *TakeAction::clone() { return new TakeAction(*this); }

void TakeAction::execute_impl() {
	static auto logger =
		mudserver::logging::getLogger("Action::TakeAction");

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

    	// get object from room by name 
    	// TODO: method to take object by name
    	boost::optional<ObjectEntity> objectToTake = boost::none;
    	// if object is null, return error msg to players
    	if (objectToTake) {
	    	// add to character's onjects
	    	// characterPerformingAction.addObject(objectToTake);    		
	    	gameManager.sendCharacterMessage(
    			characterPerformingAction->getEntityId(),
    			"Object found in room");
    	} else {
    		gameManager.sendCharacterMessage(
    			characterPerformingAction->getEntityId(),
    			"Object not found in room");
    		 
    	}

    } else {
    	// error that you need to try and take something
    	gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(),
            "Please type /'take/' <object>/'");
    } 

}
