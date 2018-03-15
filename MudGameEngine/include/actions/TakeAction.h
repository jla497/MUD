#ifndef TAKE_ACTION_H
#define TAKE_ACTION_H

#include "Action.h"
#include "gamemanager/GameManager.h"

/**
 * Take action assumes you may only take items in a room
 * and not from a player/npc, that is 'steal'
 */
class TakeAction : public Action {
  public:
  	using Action::Action;
  	void execute_impl() override;

  protected:
  	std::string description() const override { return u8"Take action"; }
  	TakeAction *clone() override; // need to change this...
};

#endif // TAKEACTION_H