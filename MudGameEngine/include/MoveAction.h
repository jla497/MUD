#ifndef MOVEACTION_H
#define MOVEACTION_H
#include "Entity.h"
#include "gamemanager/GameManager.h"

//The MoveAction class defines the behavior for when an Player moves from one Room to another.
class MoveAction : public Entity{
  public:
  	MoveAction() : Action(const std::string& entityPerformingAction,
  		const std::vector<std::string>* entitiesBeingActedUpon,
  		const mudserver::gamemanager::GameManager& gameManager);

   	void execute();
};
#endif