#ifndef ACTION_H
#define ACTION_H

#include "entities/CharacterEntity.h"
#include "entities/Entity.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace mudserver {
namespace gamemanager {
class GameManager;
class Player;
} // namespace gamemanager
} // namespace mudserver

using mudserver::gamemanager::Player;

enum class ActKeyword {
    undefined = 0,
    say,
    look,
    attack,
    move,
    program,
    timed,
    save,
    charmod,
    halt,
    swap,

    _N_ACTIONS_
};

/**
 * The Action class defines the interface that all actions implement.
 * Actions need reference to a player's character and the game state, and they
 * own an ordered collection of arguments to the action that determine what it
 * actually affects.
 */
class Action {
    using Tick = int;

  public:
    // return const so execute() cannot be called on a base action
    static const Action *base(ActKeyword keyword);

    Action() = default;
    Action(const Action &) = default;
    Action &operator=(const Action &) = default;
    Action(Action &&) = default;
    Action &operator=(Action &&) = default;
    virtual ~Action() = default;

    bool requiresAdmin() const;
    void setAdmin(bool admin) const;

    /**
     * Actions are designed to be placed in a queue. When the queue is
     * processed, execute() is called on the actions. As they have reference to
     * the game manager, they can alter state and send messages in this method.
     */
    void execute();
    virtual std::unique_ptr<Action> clone() const = 0;
    std::unique_ptr<Action>
    clone(Player &playerPerformingAction,
          std::vector<std::string> actionArguments,
          mudserver::gamemanager::GameManager &gameManager) const;

    static void registerAdminActions(const std::string &file);

  private:
    mutable bool isAdmin = true;

    virtual void execute_impl() = 0;
    friend std::ostream &operator<<(std::ostream &os, const Action &action);

    void initialize(Player &playerPerformingAction,
                    std::vector<std::string> actionArguments,
                    mudserver::gamemanager::GameManager &gameManager);

  protected:
    CharacterEntity *characterPerformingAction = nullptr;
    Player *playerPerformingAction = nullptr;
    std::vector<std::string> actionArguments;
    mudserver::gamemanager::GameManager *gameManager = nullptr;
    Tick timeRemaining = -1;

    virtual std::string description() const = 0;
};
#endif
