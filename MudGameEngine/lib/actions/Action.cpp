#include <memory>
#include <ostream>

#include "actions/Action.h"

Action::Action(std::string entityPerformingAction,
               std::vector<std::string> entitiesBeingActedUpon,
               mudserver::gamemanager::GameManager& gameManager)
    : entityPerformingAction{std::move(entityPerformingAction)},
      entitiesBeingActedUpon{std::move(entitiesBeingActedUpon)},
      gameManager{gameManager} {}

std::ostream& operator<<(std::ostream& os, const Action& action) {
    os << action.description() << ", [";
    for (const auto& entity : action.entitiesBeingActedUpon) {
        os << entity << ", ";
    }
    os << "]";
    return os;
}
