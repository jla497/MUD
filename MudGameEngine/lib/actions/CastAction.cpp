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
	if (!actionArguments.empty()) {
		//get name of spell
		auto spellName = actionArguments[0];

		//get spell using spell name
		auto spell = gameState.getSpellByName(spellName);

		//find type of spell
		auto spellType = spell.getType();

		switch(spellType) {
			case SpellType::defense:
			case SpellType::offense:
			case SpellType::swap:
				std::unique_pointer<SwapAction> swapAction = std::make_unique<SwapAction>(playerPerformingAction, actionArguments, gameManager);
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
}
//void SpellAction::execute_impl() {
//    static auto logger = mudserver::logging::getLogger("SpellAction::execute");
//    auto &gameState = gameManager.getState();
//
//
//    if (!actionArguments.empty()) {
          //get the name of the spell
//        auto spellName = actionArguments[0];
//
//        //get spell
//        auto spell = gameState.getSpell(spellName);
//
//        //is it attack, defense, mod, etc.
//        auto spellType = spell.Type;
//
//        switch (spellType) {
//            case SpellType::modification:
//                executeModSpell(spell);
//                break;
//
//            case SpellType::attack:
//                executeAttackSpell(spell);
//                break;
//
//            default:
//                logger->error("Not a valid Spell name...");
//                gameManager.sendCharacterMessage(
//                        characterPerformingAction->getEntityId(),
//                        "Not a valid Spell name...");
//                return;
//
//        }
//    }else {
//        logger->error("Not a valid Spell command...");
//        gameManager.sendCharacterMessage(
//                characterPerformingAction->getEntityId(),
//                "Not a valid Spell command...");
//        return;
//    }
//
//}
//
//void SpellAction::executeModSpell(Spell spell) {
//    for(auto& key : spell) {
//        characterPerformingAction.set(key, spell[key]);
//    }
//}

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

void CastAction::executeOffenseSpell(Spell spell) {

}

CastAction *CastAction::clone() { return new CastAction(*this); }