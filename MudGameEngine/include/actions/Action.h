#ifndef ACTION_H
#define ACTION_H

namespace mudserver {
namespace gamemanager {
class GameManager;
class Player;
} // namespace gamemanager
} // namespace mudserver

#include "entities/CharacterEntity.h"
#include "entities/Entity.h"
#include "gamemanager/GameManager.h"
#include "gamemanager/Player.h"

using mudserver::gamemanager::Player;

/**
 * The Action class defines the interface that all actions implement.
 * Actions need reference to a player's character and the game state, and they
 * own an ordered collection of arguments to the action that determine what it
 * actually affects.
 */
class Action {
    using Tick = int;
    static std::unordered_map<std::string, bool> isAdminAction;

  public:
    Action(CharacterController &controller,
           std::vector<std::string> actionArguments,
           mudserver::gamemanager::GameManager &gameManager);

    Action(const Action &) = default;
    Action &operator=(const Action &) = default;
    Action(Action &&) = default;
    Action &operator=(Action &&) = default;
    virtual ~Action() = default;

    /**
     * Actions are designed to be placed in a queue. When the queue is
     * processed, execute() is called on the actions. As they have reference to
     * the game manager, they can alter state and send messages in this method.
     */
    void execute();
    virtual std::unique_ptr<Action> clone() const = 0;

  private:
    virtual void execute_impl() = 0;
    friend std::ostream &operator<<(std::ostream &os, const Action &action);

  protected:
    virtual std::string description() const = 0;
    CharacterEntity *characterPerformingAction = nullptr;
    Player &playerPerformingAction;
    std::vector<std::string> actionArguments;
    mudserver::gamemanager::GameManager &gameManager;
    Tick timeRemaining = -1;
    CharacterController &controller;
};
#endif
