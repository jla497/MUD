#ifndef SAYACTION_H
#define SAYACTION_H

#include "Action.h"
#include "gamemanager/GameManager.h"

/**
 * The SayAction class defines the behavior for when an player sends a message
 * to every other player in the room.
 */
class ActionObserver;

class SayAction : public Action {
  public:
    using Action::Action;
    void execute_impl() override;
    std::unique_ptr<Action> clone() const override;
    void accept(ActionObserver *observer) override;

  protected:
    std::string description() const override { return u8"Say action"; }
};
#endif