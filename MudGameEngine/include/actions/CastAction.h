#ifndef CASTACTION_H
#define CASTACTION_H

#include "Action.h"
#include "Spell.h"
#include "gamemanager/GameManager.h"

class CastAction : public Action {

  public:
    using Action::Action;
    void execute_impl() override;

private:
  void executeModSpell(Spell spell);
  protected:
    std::string description() const override { return u8"Cast action"; }
}

#endif