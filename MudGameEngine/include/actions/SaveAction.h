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

    SaveAction() = default;

    void execute_impl() override;

  protected:
    std::string description() const override { return u8"Save action"; }
    std::unique_ptr<Action> clone() const override;
};
#endif // SAVEACTION_H