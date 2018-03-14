//
// Created by jla497 on 01/03/18.
//

#ifndef TIMEDACTION_H
#define TIMEDACTION_H
#include "Action.h"
#include "gamemanager/GameManager.h"

/**
 * The NullAction class is instantiated to indicate a no-op
 */
class TimedAction : public Action {
  public:
    using Action::Action;
    void execute_impl() override;
    std::unique_ptr<Action> clone() const override;

  protected:
    std::string description() const override { return u8"Timed action"; }
};
#endif // ADVENTURE2018_TIMEDACTION_H
