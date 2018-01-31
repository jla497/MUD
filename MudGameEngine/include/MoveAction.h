#ifndef MOVEACTION_H
#define MOVEACTION_H
#include "Entity.h"
#include "GameManager.h"

//The MoveAction class defines the behavior for when an Player moves from one Room to another.
class MoveAction{
  public:
   	void execute(const String& entityPerformingAction,
  		const std::vector<String>& entitiesBeingActedUpon,
  		const GameManager& gameManager);
};
#endif