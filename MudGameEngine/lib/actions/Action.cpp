#include <memory>
#include <ostream>

#include "actions/Action.h"
#include "logging.h"
#include "gamemanager/GameManager.h"

// FIXME: this should possibly work on the enum keyword rather than the
// description string
std::unordered_map<std::string, bool> Action::isAdminAction = {
    {"Program action", true}, {"Save action", true}};

Action::Action(Player &playerPerformingAction,
               std::vector<std::string> actionArguments,
               mudserver::gamemanager::GameManager &gameManager)
    : playerPerformingAction{playerPerformingAction},
      actionArguments{std::move(actionArguments)}, gameManager{gameManager} {}

void Action::execute() {
    // check if this is an admin action
    static auto logger = mudserver::logging::getLogger("Action::Action");

    auto &playerService = gameManager.getPlayerService();
    auto characterId =
        playerService.playerToCharacter(playerPerformingAction.getId());
    characterPerformingAction =
        gameManager.getState().getCharacterFromLUT(*characterId);

    logger->debug("Checking if " + description() + " is AdminAction...");
    // check if action is admin action and if character has an administrator
    // role
    if (Action::isAdminAction[description()]) {
        if (playerPerformingAction.hasAdminPrivilege()) {
            execute_impl();
        }
        else {
            logger->debug("Player does not have admin privileges!");
        }
    } else {
        execute_impl();
    }

    if (timeRemaining > 0) {
        timeRemaining--;
        auto newAction = clone();
        auto ptr = std::unique_ptr<Action>(newAction);
        gameManager.addActionToQueue(std::move(ptr));
    }
}
std::ostream &operator<<(std::ostream &os, const Action &action) {
    os << action.description() << ", [";
    for (const auto &entity : action.actionArguments) {
        os << entity << ", ";
    }
    os << "]" << std::endl;
    return os;
}
