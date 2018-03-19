#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "actions/AttackAction.h"
#include "gamemanager/GameManager.h"
#include "logging.h"


//@Aram: I dont know how much you've implemented but this is roughly what I think could work in pseudocode.
// 
void CastAction::execute_impl() {
	static auto logger = mudserver::logging::getLogger("SpellAction::execute");
	auto &gameState = gameManager.getState();
	if (actionArguments.empty()) {
		gameManager.sendCharacterMessage(
			characterPerformingAction->getEntityId(),
			"Please enter a spell name.");
        logger->debug("No spell name found...");
        return;
	}

	auto characterCurrentRoom = gameState.getCharacterLocation(*characterPerformingAction);
    if (!characterCurrentRoom) {
        logger->error(
            "Character is not in a room! Suspect incorrect world init");
        return;
    }

	if (actionArguments.size() == 1) {
		//spell name is only one word, player did not provide a character name as an arg
		//get name of spell:
		auto spellName = boost::to_lower_copy(actionArguments.at(0));
	} else {
		/*if the action arguments have more than 1 element, then:
		1. Spell name is more than one word
		2. Spell has another character's name as the last argument
		*/
		std::string lastElement = actionArguments.at(actionArguments.size() - 1);
		//vector containing character name that was passed in by player as argument:
		std::vector<std::string> characterArg;
		CharacterEntity *victim = nullptr;
		
		//get all characters in room
		auto allCharIdsInCurrentRoom = gameState.getCharactersInRoom(characterCurrentRoom);

		//check if there is an existing character in room that matches the last argument
		if (!allCharIdsInCurrentRoom.empty()) {
			for (auto characterID : allCharIdsInCurrentRoom) {
				auto currentChar = gameState.getCharacterFromLUT(characterID);
				auto currentCharShortDesc = currentChar.getShortDesc();
				if (boost::to_lower_copy(currentCharShortDesc) == boost::to_lower_copy(lastElement)) {
					characterArg.push_back(currentCharShortDesc);
					victim = currentChar;
				}
			}
		}

		if (characterArg.empty()) {
			std::string joined = boost::algorithm::join(actionArguments, " ");
			auto spellName = boost::to_lower_copy(joined);
		}
	}

	//get spell using spell name
	auto spell = gameState.getSpellByName(spellName);

	if (!spell) {
		logger->error("Not a valid spell...");
		gameManager.sendCharacterMessage(
			characterPerformingAction->getEntityId(),
			"Not a valid spell...");
		return;
	}

	//find type of spell
	auto spellType = spell.getType();

	switch(spellType) {
		case SpellType::defense:
			executeDefenseSpell(spell);
		case SpellType::offense:
			executeOffenseSpell(spell, victim);
		case SpellType::swap:
			std::unique_pointer<SwapAction> swapAction = std::make_unique<SwapAction>(playerPerformingAction, characterArg, gameManager);
			swapAction->execute();
			break;
		case SpellType::decoy:
			std::unique_pointer<DecoyAction> decoyAction = std::make_unique<DecoyAction>(playerPerformingAction, actionArguments, gameManager);
			decoyAction->execute();
			break;
		default:
			logger->error("Not a valid spell...");
			gameManager.sendCharacterMessage(
				characterPerformingAction->getEntityId(),
				"Not a valid spell...");
			return;
		
	}
}

void CastAction::executeDefenseSpell(Spell spell) {
	CombatComponent *combatComponent = characterPerformingAction.getCombatComponent();
	charLevel = characterPerformingAction.getLevel();
	charMana = characterPerformingAction.getMana();
	if (spell.isEnoughMana(charMana) 
		&& spell.isCharacterValidLevel(charLevel)) {
		int healAmount = spell.calculateSpellEffect(charLevel);
		combatComponent->heal(healAmount);
	}
}

void CastAction::executeOffenseSpell(Spell spell, CharacterEntity &victim) {
	if (!victim) {
		CombatComponent *combatComponent = victim->getCombatComponent();
		charLevel = characterPerformingAction.getLevel();
		charMana = characterPerformingAction.getMana();
		if (spell.isEnoughMana(charMana) 
			&& spell.isCharacterValidLevel(charLevel)) {
			int dmgAmount = spell.calculateDamage(charLevel);
			if(combatComponent->damage(dmgAmount)) {
				//character was killed;
				gameState.killCharacter(victim);
			}
		}
	} else {
		logger->error("Victim is either not in the room or victim name is invalid...");
			gameManager.sendCharacterMessage(
				characterPerformingAction->getEntityId(),
				"Victim is either not in the room or victim name is invalid...");
		}
}

CastAction *CastAction::clone() { return new CastAction(*this); }