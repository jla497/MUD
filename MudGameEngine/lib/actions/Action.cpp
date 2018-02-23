#include <memory>
#include <ostream>

#include "actions/Action.h"
#include "logging.h"

std::unordered_map<std::string, bool> Action::isAdminAction = {
    {"Program action", true}};

Action::Action(PlayerCharacter &characterPerformingAction,
               std::vector<std::string> actionArguments,
               mudserver::gamemanager::GameManager &gameManager)
    : characterPerformingAction{characterPerformingAction},
      actionArguments{std::move(actionArguments)}, gameManager{gameManager} {}

void Action::execute() {
    // check if this is an admin action
    static auto logger = mudserver::logging::getLogger("Action::Action");
    logger->info("Checking if Action is AdminAction...");

    // check if action is admin action and if character has an administrator
    // role
    if (Action::isAdminAction[description()]) {
        if (characterPerformingAction.getAdministrator() != nullptr) {
            execute_impl();

        } else {
            return;
        }
    } else {
        execute_impl();
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
