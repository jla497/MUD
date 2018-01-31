#ifndef ACTION_H
#define ACTION_H
#include "Entity.h"
#include "gamemanager/GameManager.h"

//The Action class defines the interface that all actions conform to.
class Action{
  public:
    virtual ~Action();
    //pass name of entities involved so we can parse them right before we want to execute
  	virtual void execute(const std::string& entityPerformingAction,
  		const std::vector<std::string>& entitiesBeingActedUpon,
  		const mudserver::gamemanager::GameManager& gameManager) = 0;
};
#endif