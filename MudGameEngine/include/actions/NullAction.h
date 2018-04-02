#ifndef NULLACTION_H
#define NULLACTION_H

#include "Action.h"
#include "gamemanager/GameManager.h"

/**
 * The NullAction class is instantiated to indicate a no-op
 */
class NullAction : public Action {
  public:
    using Action::Action;

    NullAction() = default;

    void execute_impl() override;
    std::unique_ptr<Action> clone() const override;

  protected:
    std::string description() const override { return u8"Null action"; }
};
#endif // NULLACTION_H