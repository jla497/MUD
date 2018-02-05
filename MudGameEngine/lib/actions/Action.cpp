#include <memory>
#include <ostream>

#include "actions/Action.h"

Action::Action(PlayerCharacter& characterPerformingAction,
               std::vector<std::string> entitiesBeingActedUpon,
               mudserver::gamemanager::GameManager& gameManager)
    : characterPerformingAction{characterPerformingAction},
      actionArguments{std::move(entitiesBeingActedUpon)},
      gameManager{gameManager} {}

std::ostream& operator<<(std::ostream& os, const Action& action) {
    os << action.description() << ", [";
    for (const auto& entity : action.actionArguments) {
        os << entity << ", ";
    }
    os << "]" << std::endl;
    return os;
}
