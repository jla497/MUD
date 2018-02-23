#include <memory>
#include <ostream>

#include "actions/Action.h"
#include "logging.h"

Action::Action(PlayerCharacter &characterPerformingAction,
               std::vector<std::string> actionArguments,
               mudserver::gamemanager::GameManager &gameManager)
    : characterPerformingAction{characterPerformingAction},
      actionArguments{std::move(actionArguments)}, gameManager{gameManager} {}

void Action::execute() {
  //check if this is an admin action
  static auto logger = mudserver::logging::getLogger("Action::Action");
  logger->info("Checking if Action is AdminAction...");
  execute_impl();
}
std::ostream &operator<<(std::ostream &os, const Action &action) {
    os << action.description() << ", [";
    for (const auto &entity : action.actionArguments) {
        os << entity << ", ";
    }
    os << "]" << std::endl;
    return os;
}
