#ifndef ATTACKACTION_H
#define ATTACKACTION_H
#include "Action.h"
#include "gamemanager/GameManager.h"

//The AttackAction class defines the behavior for when a player attacks a creature
class AttackAction : public Action{
  public:
  	AttackAction(const std::string& entityPerformingAction, 
  		const std::vector<std::string>* entitiesBeingActedUpon,
  		const mudserver::gamemanager::GameManager& gameManager) : 
  		Action(entityPerformingAction,entitiesBeingActedUpon,& gameManager);
  	
  	void execute();
};
#endif