#include <resources/DataFields.h>

#include "actions/PrgmAction.h"
#include "resources/commands.h"
#include "gamemanager/GameManager.h"
#include "logging.h"

using boost::algorithm::to_lower;
using namespace mudserver::resources::commands;

std::unordered_map<std::string, PrgmAction::PrgmKeyword> PrgmAction::prgmLookup = {
        {NPC, PrgmAction::PrgmKeyword::npc},
        {PC, PrgmAction::PrgmKeyword::pc},
        {OBJECT, PrgmAction::PrgmKeyword::object}
};
void PrgmAction::execute_impl() {


    static auto logger =
        mudserver::logging::getLogger("ProgramAction::execute");

    std::string userinfo(
            "userid: " +
            std::to_string(characterPerformingAction.getEntityId().getId()));
    logger->info(userinfo);

    if (actionArguments.empty()) {
        logger->error("Not a valid Program command...");
        gameManager.sendCharacterMessage(
                characterPerformingAction.getEntityId(),
                "Not a valid Program command...");
        return;
    }

    auto cmd = actionArguments[0];
    to_lower(cmd);
    auto actionTypeIter = prgmLookup.find(cmd);

    auto actionType = (actionTypeIter == prgmLookup.end())
                            ? PrgmKeyword::undefined
                            : actionTypeIter->second;


    // get first arg: Possible options: {npc, character, object ...}
    switch(actionType) {
        case PrgmKeyword::npc: {
            prgmNpc();
            break;
        }
        case PrgmKeyword::pc: {
            prgmPc();
            break;
        }
        case PrgmKeyword::object: {
            prgmObject();
            break;
        }
        default:
            logger->debug("not a valid program command");
    }
    //switch statements
}

void PrgmAction::prgmNpc() {
    logger->debug("prgmNpc executed");
}

void PrgmAction::prgmPc() {
    logger->debug("prgmPc executed");
}


void PrgmAction::prgmObject() {
    logger->debug("prgmObject executed");
}
