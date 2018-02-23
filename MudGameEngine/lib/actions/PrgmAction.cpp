#include "actions/PrgmAction.h"
#include "gamemanager/GameManager.h"
#include "logging.h"

void PrgmAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("ProgramAction::execute");
    logger->debug("Program Action executed!");
}
