#ifndef ACTION_H
#define ACTION_H

#include "Entity.h"
#include "gamemanager/GameManager.h"

//The Action class defines the interface that all actions conform to.
class Action{
  public:
  	Action(const std::string& entityPerformingAction,
  		const std::vector<std::string>* entitiesBeingActedUpon,
  		const mudserver::gamemanager::GameManager& gameManager);

  	virtual void execute() = 0;

  private:
    std::string& entityPerformingAction;
    std::vector<std::string>* entitiesBeingActedUpon;
    mudserver::gamemanager::GameManager& gameManager;
};
#endif
