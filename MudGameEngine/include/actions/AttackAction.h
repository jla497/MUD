#ifndef ATTACKACTION_H
#define ATTACKACTION_H

#include "Action.h"
#include "gamemanager/GameManager.h"

/**
 * The AttackAction class defines the behavior for when a player character
 * attacks a creature or other character.
 */
class AttackAction : public Action {
  public:
    using Action::Action;
    void execute() override;

  protected:
    std::string description() const override { return u8"Attack action"; }
};
#endif