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
    std::unique_ptr<Action> clone() const override;

  private:
  	CharacterEntity *victim = nullptr;

    void executeDefenseSpell(Spell &spell);
    void executeOffenseSpell(Spell &spell);

    //returns true if character has enough mana and is at a high enough level to execute the spell
    bool canExecuteSpell(Spell &spell);

    //displays messages to players about the spell currently being casted
    void displayMessages(Spell &spell, bool isHit);

    //helper function to display a message to the entire room except for the player who cast the spell
    void displayMessageToRoom(std::string message);
  protected:
    std::string description() const override { return u8"Cast action"; }
};

#endif