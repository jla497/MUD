#ifndef ACTION_H
#define ACTION_H

namespace mudserver {
namespace gamemanager { class GameManager; }
}

#include "entities/Entity.h"
#include "entities/PlayerCharacter.h"

// The Action class defines the interface that all actions conform to.
class Action {
public:
    Action(PlayerCharacter& entityPerformingAction,
           std::vector<std::string> entitiesBeingActedUpon,
           mudserver::gamemanager::GameManager& gameManager);

    virtual void execute() = 0;

    friend std::ostream& operator<<(std::ostream& os, const Action& action);
protected:
    virtual std::string description() const = 0;
    PlayerCharacter& characterPerformingAction;
    std::vector<std::string> entitiesBeingActedUpon;
    mudserver::gamemanager::GameManager& gameManager;
};
#endif
