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
    void execute() override;

  protected:
    std::string description() const override { return u8"Null action"; }
};
#endif // NULLACTION_H