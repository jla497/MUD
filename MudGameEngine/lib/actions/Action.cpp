#include <memory>
#include <ostream>

#include "actions/Action.h"
#include "logging.h"
#include "gamemanager/GameManager.h"

std::unordered_map<std::string, bool> Action::isAdminAction = {
    {"Program action", true}};

Action::Action(CharacterEntity &characterPerformingAction,
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
        // TODO check if player has admin privilege else return
        execute_impl();
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
