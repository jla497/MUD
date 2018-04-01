#include <boost/algorithm/string.hpp>
#include <memory>
#include <string>
#include <vector>

#include "actions/CastAction.h"
#include "logging.h"

std::unique_ptr<Action> CastAction::clone() const {
    return std::make_unique<CastAction>(*this);
}

void CastAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("CastAction::execute");
    auto &gameState = gameManager.getState();
    if (actionArguments.empty()) {
        gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(),
            "Please enter a spell name.");
        logger->debug("No spell name found...");
        return;
    }

    auto characterCurrentRoom =
        gameState.getCharacterLocation(*characterPerformingAction);
    if (!characterCurrentRoom) {
        logger->error(
            "Character is not in a room! Suspect incorrect world init");
        return;
    }

    std::string spellName = "";
    // vector containing character name that was passed in by player as
    // argument:
    std::vector<std::string> characterArg;

    if (actionArguments.size() == 1) {
        // spell name is only one word, player did not provide a character name
        // as an arg
        // get name of spell:
        spellName = boost::to_lower_copy(actionArguments.at(0));
    } else {
        /*if the action arguments have more than 1 element, then:
        1. Spell name is more than one word
        2. Spell has another character's name as the last argument
        */

        std::string lastElement =
            actionArguments.at(actionArguments.size() - 1);

        // get all characters in room
        auto allCharIdsInCurrentRoom =
            gameState.getCharactersInRoom(characterCurrentRoom);

        // check if there is an existing character in room that matches the last
        // argument
        if (!allCharIdsInCurrentRoom.empty()) {
            for (auto characterID : allCharIdsInCurrentRoom) {
                auto currentChar = gameState.getCharacterFromLUT(characterID);
                auto currentCharShortDesc = currentChar->getShortDesc();
                if (boost::to_lower_copy(currentCharShortDesc) ==
                    boost::to_lower_copy(lastElement)) {
                    characterArg.push_back(currentCharShortDesc);
                    victim = currentChar;
                }
            }
        }

        if (characterArg.empty()) {
            std::string joined = boost::algorithm::join(actionArguments, " ");
            spellName = boost::to_lower_copy(joined);
        } else {
            actionArguments.erase(actionArguments.end());
            std::string joined = boost::algorithm::join(actionArguments, " ");
            spellName = boost::to_lower_copy(joined);
        }
    }

    // get spell using spell name
    auto spell = gameState.getSpellByName(spellName);

    if (!spell) {
        logger->error("Not a valid spell...");
        gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(), "Not a valid spell...");
        return;
    }

    // find type of spell
    auto spellType = spell->getType();

    switch (spellType) {
    case Spell::SpellType::defense:
        executeDefenseSpell(*spell);
        break;

    case Spell::SpellType::offense:
        if (victim) {
            executeOffenseSpell(*spell);
        } else {
            logger->error("Victim is either not in the room or victim name is "
                          "invalid...");
            gameManager.sendCharacterMessage(
                characterPerformingAction->getEntityId(),
                "Victim is either not in the room or victim name is "
                "invalid...");
        }
        break;

    case Spell::SpellType::swap: {
        SwapAction swapAction{playerPerformingAction, characterArg,
                              gameManager};
        swapAction.execute();
    } break;

    case Spell::SpellType::decoy: {
        DecoyAction decoyAction{playerPerformingAction, actionArguments,
                                gameManager};
        decoyAction.execute();
    } break;

    default:
        logger->error("Not a valid spell...");
        gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(), "Not a valid spell...");
        return;
    }
}

void CastAction::executeDefenseSpell(Spell &spell) {
    static auto logger = mudserver::logging::getLogger("DefenseSpell::execute");
    CombatComponent *combatComponent =
        characterPerformingAction->getCombatComponent();

    // defense spells affect only the char performing the action
    // therefore, they are the "victim" of the spell
    victim = characterPerformingAction;

    if (canExecuteSpell(spell)) {
        displayMessages(spell, true);

        auto charLevel = characterPerformingAction->getLevel();
        auto healAmount = spell.calculateSpellEffect(charLevel);
        combatComponent->heal(healAmount);
        characterPerformingAction->subtractMana(spell.getMana());
    }
}

void CastAction::executeOffenseSpell(Spell &spell) {
    static auto logger = mudserver::logging::getLogger("OffenseSpell::execute");
    auto &gameState = gameManager.getState();
    CombatComponent *combatComponent = victim->getCombatComponent();

    if (canExecuteSpell(spell)) {
        displayMessages(spell, true);

        auto charLevel = characterPerformingAction->getLevel();
        auto dmgAmount = spell.calculateDamage(charLevel);

        combatComponent->damage(dmgAmount);
        if (combatComponent->isCharacterDead()) {
            // character was killed;
            gameState.killCharacter(*victim);
        }
        characterPerformingAction->subtractMana(spell.getMana());
    }
}

bool CastAction::canExecuteSpell(Spell &spell) {
    auto charLevel = characterPerformingAction->getLevel();
    auto charMana = characterPerformingAction->getMana();

    if (!spell.isCharacterValidLevel(charLevel)) {
        gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(),
            "Character needs to be at least level " +
                std::to_string(spell.getMinLevel()) +
                " to perform this spell...");
        return false;
    }

    if (!spell.isEnoughMana(charMana)) {
        gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(),
            "Character only has " + std::to_string(charMana) + "/" +
                std::to_string(spell.getMana()) +
                " mana to perform this spell...");
        return false;
    }

    return true;
}

void CastAction::displayMessages(Spell &spell, bool isHit) {
    std::string victimName = "";
    if (victim) {
        victimName = victim->getShortDesc();
    }

    Spell::DisplayMessages messages = spell.getDisplayMessages(
        characterPerformingAction->getShortDesc(), victimName, "");

    if (isHit) {
        // spell has successfully hit target
        if (spell.getType() != Spell::SpellType::defense &&
            messages.hitchar.length() > 0) {
            /*
             if spell is of defense type, do not send this message
             this is because defense spells should affect the char performing
             the action
             which means the char performing the action is the "victim" of the
             spell
            */
            gameManager.sendCharacterMessage(
                characterPerformingAction->getEntityId(), messages.hitchar);
        }
        if (messages.hitroom.length() > 0) {
            displayMessageToRoom(messages.hitroom);
        }
        if (victim && messages.hitvict.length() > 0) {
            gameManager.sendCharacterMessage(victim->getEntityId(),
                                             messages.hitvict);
        }
    } else {
        // spell missed the target
        if (spell.getType() != Spell::SpellType::defense &&
            messages.misschar.length() > 0) {

            gameManager.sendCharacterMessage(
                characterPerformingAction->getEntityId(), messages.misschar);
        }
        if (messages.missroom.length() > 0) {
            displayMessageToRoom(messages.missroom);
        }
        if (victim && messages.missvict.length() > 0) {
            gameManager.sendCharacterMessage(victim->getEntityId(),
                                             messages.missvict);
        }
    }
}

void CastAction::displayMessageToRoom(std::string message) {
    static auto logger =
        mudserver::logging::getLogger("CastAction::displayMessages");
    auto &gameState = gameManager.getState();
    auto currentRoom =
        gameState.getCharacterLocation(*characterPerformingAction);
    // get the ids of all characters in the room:
    auto charactersInRoom = gameState.getCharactersInRoom(currentRoom);
    if (charactersInRoom.empty()) {
        logger->debug("Room has no characters...");
        return;
    }

    // send the message to all the players in the room EXCEPT for
    // the character peforming the action, and the victim (if there is one)
    for (auto character : charactersInRoom) {
        if (!(character == characterPerformingAction->getEntityId())) {
            // check if victim exists before accessing victim's id
            if (victim) {
                if (!(character == victim->getEntityId())) {
                    // only send the message if current character is not the
                    // victim
                    gameManager.sendCharacterMessage(character, message);
                }
            } else {
                gameManager.sendCharacterMessage(character, message);
            }
        }
    }
}