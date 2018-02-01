#ifndef ATTACKACTION_H
#define ATTACKACTION_H
#include "Entity.h"
#include "gamemanager/GameManager.h"

//The AttackAction class defines the behavior for when a player attacks a creature
class AttackAction : public Entity{
  public:
  	AttackAction(const std::string& entityPerformingAction, 
  		const std::vector<std::string>* entitiesBeingActedUpon,
  		const mudserver::gamemanager::GameManager& gameManager);
  	
  	void execute();
};
#endif