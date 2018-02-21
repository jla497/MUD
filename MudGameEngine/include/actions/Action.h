#ifndef ACTION_H
#define ACTION_H

namespace mudserver {
namespace gamemanager {
class GameManager;
}
}

#include "entities/Entity.h"
#include "entities/PlayerCharacter.h"
#include <string>
#include <vector>

/**
 * The Action class defines the interface that all actions implement.
 * Actions need reference to a player's character and the game state, and they
 * own an ordered collection of arguments to the action that determine what it
 * actually affects.
 */
class Action {
public:
    Action(PlayerCharacter& characterPerformingAction,
           std::vector<std::string> actionArguments,
           mudserver::gamemanager::GameManager& gameManager);

    /**
     * Actions are designed to be placed in a queue. When the queue is
     * processed, execute() is called on the actions. As they have reference to
     * the game manager, they can alter state and send messages in this method.
     */
    virtual void execute() = 0;

    friend std::ostream& operator<<(std::ostream& os, const Action& action);

protected:
    virtual std::string description() const = 0;
    PlayerCharacter& characterPerformingAction;
    std::vector<std::string> actionArguments;
    mudserver::gamemanager::GameManager& gameManager;
};
#endif
