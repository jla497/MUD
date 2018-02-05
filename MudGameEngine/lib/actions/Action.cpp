#include <memory>
#include <ostream>

#include "actions/Action.h"

Action::Action(PlayerCharacter* playerCharacter,
               std::vector<std::string> entitiesBeingActedUpon,
               mudserver::gamemanager::GameManager& gameManager)
    : playerCharacter{playerCharacter},
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
