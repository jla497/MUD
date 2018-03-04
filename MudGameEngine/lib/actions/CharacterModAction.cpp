#include <string>
#include <vector>
#include <boost/format.hpp>

#include "actions/CharacterModAction.h"
#include "resources/commands.h"
#include "resources/ActionMessages.h"

namespace com = mudserver::resources::commands;
namespace mes = mudserver::resources::actions;

CharacterModAction *CharacterModAction::clone() { return new CharacterModAction(*this); }

void CharacterModAction::execute_impl() {
    auto characterId = gameManager.getPlayerService().playerToCharacter(
        playerPerformingAction.getId());
    auto character = gameManager.getState().getCharacterFromLUT(*characterId);

    switch (actionArguments.size()) {

    case 1:
        // just displaying a single property
        if (actionArguments.at(0) == com::CNAME) {
            showCharacterName(*character);
        }
        return;
    case 2:
        if (actionArguments.at(0) == com::CNAME) {
            character->setShortDesc(actionArguments.at(1));
            showCharacterName(*character);
        }
        return;
    case 0:
    default:
        // no arguments - should maybe list the character's attributes
        break;
    }
}

void CharacterModAction::showCharacterName(const CharacterEntity &character) {
    gameManager.sendCharacterMessage(
        character.getEntityId(),
        (boost::format(mes::YOURNAME) % character.getShortDesc())
            .str());
}
