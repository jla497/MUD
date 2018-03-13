#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "actions/AttackAction.h"
#include "gamemanager/GameManager.h"
#include "logging.h"


//@Aram: I dont know how much you've implemented but this is roughly what I think could work in pseudocode.
// 
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

SpellAction *SpellAction::clone() { return new SpellAction(*this); }