#include "actions/DecoyAction.h"
#include "logging.h"

void DecoyAction::execute_impl() {
	static auto logger = mudserver::getLogger("Action::DecoyAction");

	std::string userinfo(
        "userid: " +
        std::to_string(characterPerformingAction.getEntityId().getId()));
    logger->info(userinfo);

	// get room char is in
    auto &gameState = gameManager.getState();
    RoomEntity *room =
        gameState.getCharacterLocation(characterPerformingAction);

    if (!room) {
        logger->error("Character not found in any room...");
        return;
    }
    std::string roomInfo("roomid: " + std::to_string(room->getId()));
    logger->info(roomInfo);
    
    // get decoy spell information; spell may not be one word
    std::string spellName = "";
    for (word : actionArguments) {
    	spellName += word + " ";
    }
    spellName = spellName.substr(0, spellName.size()-1); //cut last space    
    boost::algorithm::to_lower(spellName);
    auto spell = gameState.getSpellByName(spellName);
    if (spell = nullptr) {
    	logger->debug("Spell not found, cast nothing. Maybe add error msg?");
    	return;
    } 

    // Process Spell
    // First time only, set the time according to spell object
	if (timeRemaining == -1) {
		timeRemaining = spell.getDuration();
		// check character's mana and perform action if possible
		if (characterPerformingAction.getMana() >= spell.getMana()) {		
			auto newDecoy = characterPerformingAction; // copy constructor?
			ourDecoy = newDecoy.getEntityId();
			gameState.addCharacterRoomRelationToLUT(newDecoy.getEntityId(), room->getId());			
		} else {
			logger->debug("Spell not cast, not enough mana");
		}
	} else if (timeRemaining == 0) {		
		gameState.removeCharacterByUniqueId(ourDecoy); //method doesn't exist yet
	} else {
		// decoy exists
	}
	std::unique_ptr<Action> decremenentedDecoyAction = this.clone();
	decremenentedDecoyAction.setTimeRemaining(timeRemaining - 1);
	gameState.enqueueAction(decremenentedDecoyAction);

}