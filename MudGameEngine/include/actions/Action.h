#ifndef ACTION_H
#define ACTION_H

class Action;

#include "entities/Entity.h"
#include "gamemanager/GameManager.h"

// The Action class defines the interface that all actions conform to.
class Action {
public:
    Action(std::string entityPerformingAction,
           std::vector<std::string> entitiesBeingActedUpon,
           mudserver::gamemanager::GameManager& gameManager);

    virtual void execute() = 0;

    friend std::ostream& operator<<(std::ostream& os, const Action& action);
protected:
    virtual std::string description() const = 0;
    std::string entityPerformingAction;
    std::vector<std::string> entitiesBeingActedUpon;
    mudserver::gamemanager::GameManager& gameManager;
};
#endif
