#include <memory>
#include <ostream>

#include "actions/Action.h"
#include "gamemanager/GameManager.h"

Action::Action(CharacterEntity &characterPerformingAction,
               std::vector<std::string> actionArguments,
               mudserver::gamemanager::GameManager &gameManager)
    : characterPerformingAction{characterPerformingAction},
      actionArguments{std::move(actionArguments)}, gameManager{gameManager} {}
void Action::execute() {
    // check if this is an admin action
    execute_impl();
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
