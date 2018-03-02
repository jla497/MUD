#ifndef SAYACTION_H
#define SAYACTION_H

#include "Action.h"
#include "gamemanager/GameManager.h"

/**
 * The SayAction class defines the behavior for when an player sends a message
 * to every other player in the room.
 */
class SayAction : public Action {
  public:
    using Action::Action;
    void execute_impl();
    SayAction * clone();

  protected:
    std::string description() const override { return u8"Say action"; }
};
#endif