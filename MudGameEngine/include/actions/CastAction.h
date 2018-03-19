#ifndef CASTACTION_H
#define CASTACTION_H

#include "Action.h"
#include "Spell.h"
#include "actions/SwapAction.h"
#include "actions/DecoyAction.h"
#include "gamemanager/GameManager.h"

class CastAction : public Action {

  public:
    using Action::Action;
    void execute_impl() override;
    CastAction *clone() override;

  private:
    void executeDefenseSpell(Spell &spell);
    void executeOffenseSpell(Spell &spell, CharacterEntity &victim);
  protected:
    std::string description() const override { return u8"Cast action"; }
};

#endif