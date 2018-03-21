
#include <memory>

#include "actions/DecoyAction.h"
#include "logging.h"

std::unique_ptr<Action> DecoyAction::clone() const {
    return std::make_unique<DecoyAction>(*this);
}

void DecoyAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("Action::DecoyAction");

    std::string userinfo(
        "userid: " +
        std::to_string(characterPerformingAction->getEntityId().getId()));
    logger->info(userinfo);

    // get room char is in
    auto &gameState = gameManager.getState();
    RoomEntity *room =
        gameState.getCharacterLocation(*characterPerformingAction);

    if (!room) {
        logger->error("Character not found in any room...");
        return;
    }
    std::string roomInfo("roomid: " + std::to_string(room->getId()));
    logger->info(roomInfo);

    // get decoy spell information; spell may not be one word
    // std::string spellName = "";
    // for (word : actionArguments) {
    // 	spellName += word + " ";
    // }
    // spellName = spellName.substr(0, spellName.size()-1); //cut last space
    // boost::algorithm::to_lower(spellName);
    // auto spell = gameState.getSpellByName(spellName);
    // if (spell = nullptr) {
    // 	logger->debug("Spell not found, cast nothing. Maybe add error msg?");
    // 	return;
    // }

    // Process Spell
    // First time only, set the time according to spell object
    if (timeRemaining == -1) {
        // timeRemaining = spell.getDuration(); // no spell info
        timeRemaining = 12;
        // check character's mana and perform action if possible
        // if (characterPerformingAction.getMana() >= spell.getMana()) {// no
        // spell
        if (characterPerformingAction->getMana() >= 0) {
            auto newDecoy = characterPerformingAction; // copy constructor?
            ourDecoyId =
                newDecoy->getEntityId(); // to bind decoy to this action obj
            gameState.addCharacter(*newDecoy, room->getId());
            logger->debug("decoy added in room " +
                          std::to_string(room->getId()));
        } else {
            logger->debug("Spell not cast, not enough mana");
        }
    } else if (timeRemaining == 0) {
        gameState.removeCharacterByUniqueId(ourDecoyId);
        logger->debug("decoy removed from room " +
                      std::to_string(room->getId()));
    } else {
        // decoy exists and will keep existing for this tick
    }
}

