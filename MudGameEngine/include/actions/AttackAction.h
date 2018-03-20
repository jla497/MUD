#ifndef ATTACKACTION_H
#define ATTACKACTION_H

#include "Action.h"
#include "CombatSimulation.h"
#include "gamemanager/GameManager.h"

/**
 * The AttackAction class defines the behavior for when a character
 * attacks an other character.
 */
class AttackAction : public Action {
  public:
    using Action::Action;
    void execute_impl() override;
    std::unique_ptr<Action> clone() const override;

  protected:
    std::string description() const override { return u8"Attack action"; }
};
#endif
