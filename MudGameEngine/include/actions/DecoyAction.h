#ifndef DECOYACTION_H
#define DECOYACTION_H

#include "Action.h"
#include "gamemanager/GameManager.h"
// #include "resources/UniqueId.h"
#include <queue>

/**
 * The DecoyAction class defines the behavior for when an player casts
 * a decoy spell. A character can create as many decoys as they want
 * as long as they have enough mana to cast the spell
 * 		A decoy looks exactly as the character that decoy
 * 		Decoys last a certain number of ticks/time? TODO
 *  	A spell costs X amount of mana
 */
class DecoyAction : public Action {

  public:
    using Action::Action;
    void execute_impl() override;
    std::unique_ptr<Action> clone() const override;

  private:
    UniqueId ourDecoyId; // bind the decoy made by this Action

    bool canExecuteSpell(CharacterEntity *characterPerformingAction);


	const int DEFAULT_TIME_REMAINING = 12;
	const unsigned int MANA_COST = 2;

  protected:
    std::string description() const override { return u8"Decoy action"; }
    const unsigned int MAX_LOOK_ARGS = 0;
};
#endif