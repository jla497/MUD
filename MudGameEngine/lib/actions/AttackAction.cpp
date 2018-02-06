#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "actions/AttackAction.h"
#include "gamemanager/GameManager.h"
#include "logging.h"
AttackAction *AttackAction::clone() { return new AttackAction(*this); }

void AttackAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("AttackAction::execute");

  
    // if we didnt find the target we tell the player
    logger->info("No Target found");
    gameManager.sendCharacterMessage(attackingCharactersUniqueId,
                                     "Attack failed: could not find " +
                                         nameOfAttackTarget);
}
