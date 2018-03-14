#ifndef SPELLACTION_H
#define SPELLACTION_H

#include "Action.h"
#include "gamemanager/GameManager.h"

class SpellAction : public Action {
  private:
    std::vector<Spell> spells;

  public:
    using Action::Action;
    void execute() override;
    std::unique_ptr<Action> clone() const override;

  protected:
    std::string description() const override { return u8"Spell action"; }
}

#endif