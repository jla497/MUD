#ifndef SAVEACTION_H
#define SAVEACTION_H

#include "Action.h"
#include "gamemanager/GameManager.h"

/**
 * The SaveAction class saves game state
 */
class SaveAction : public Action {
  public:
    using Action::Action;
    void execute_impl() override;

  protected:
    std::string description() const override { return u8"Save action"; }
};
#endif // SAVEACTION_H