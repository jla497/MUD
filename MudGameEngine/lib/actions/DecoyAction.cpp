
#include <memory>

#include "actions/DecoyAction.h"
#include "entities/CombatComponent.h"
#include "entities/ObjectEntity.h"
#include "logging.h"

std::unique_ptr<Action> DecoyAction::clone() const {
    return std::make_unique<DecoyAction>(*this);
}

void DecoyAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("Action::DecoyAction");

    // Decoy has been made, wati until time is up
    if (timeRemaining > 0) {
        // logger->debug("decoy already exists");
        return;
    }

    // get room char is in
    auto &gameState = gameManager->getState();
    RoomEntity *characterCurrentRoom =
        gameState.getCharacterLocation(*characterPerformingAction);

    // Decoy time is up, destroy decoy object in room
    if (timeRemaining == 0) {
        characterCurrentRoom->removeObject(ourDecoyId);
        std::string logMsg = characterPerformingAction->getShortDesc() +
                             "'s decoy has been removed";
        logger->debug(logMsg);
        return;
    }

    if (!canExecuteSpell(characterPerformingAction)) {
        // logger->debug("Char not enough mana");
        return; // canExecuteSpell already sends error msg to player
    }

    // Timer hasn't been set yet, start the initial DECOY
    timeRemaining = DecoyAction::DEFAULT_TIME_REMAINING;

    auto charCombatComponent = characterPerformingAction->getCombatComponent();
    if (charCombatComponent->getCombatState() == CombatStates::FIGHTING) {
        charCombatComponent->endCombatState();
        charCombatComponent->setEnemiesName("");
        // Nothing to do for enemy's combat state since only references enemy
        // name...
    }

    // TODO: make fake char instead?
    auto decoyObject = ObjectEntity();
    decoyObject.setShortDesc(characterPerformingAction->getShortDesc());
    ourDecoyId = decoyObject.getEntityId();
    characterCurrentRoom->addObject(decoyObject);

    gameManager->sendCharacterMessage(
        characterPerformingAction->getEntityId(),
        "You have created a decoy called " + decoyObject.getShortDesc() +
            " in room " + characterCurrentRoom->getName());

    std::string logMsg2 =
        characterPerformingAction->getShortDesc() + " has created a decoy";
    logger->debug(logMsg2);
}

bool DecoyAction::canExecuteSpell(CharacterEntity *characterPerformingAction) {
    if (unsigned int charMana =
            characterPerformingAction->getMana() < DecoyAction::MANA_COST) {
        gameManager->sendCharacterMessage(
            characterPerformingAction->getEntityId(),
            "You only have " + std::to_string(charMana) + "/" +
                std::to_string(DecoyAction::MANA_COST) +
                " mana is needed to perform this spell.");
        return false;
    } else {
        characterPerformingAction->subtractMana(MANA_COST);
        // fall-through to return true
    }
    return true;
}
