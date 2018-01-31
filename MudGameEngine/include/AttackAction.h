#ifndef ATTACKACTION_H
#define ATTACKACTION_H
#include "Entity.h"
#include "GameManager.h"

//The AttackAction class defines the behavior for when a player attacks a creature
class AttackAction{
  public:
  	void execute(const String& entityPerformingAction,
  		const std::vector<String>& entitiesBeingActedUpon,
  		const GameManager& gameManager);
};
#endif