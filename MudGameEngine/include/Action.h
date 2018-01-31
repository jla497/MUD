#ifndef ACTION_H
#define ACTION_H
#include "Entity.h"
#include "GameManager.h"

//The Action class defines the interface that all actions conform to.
class Action{
  public:
    virtual ~Action();
    //pass name of entities involved so we can parse them right before we want to execute
  	virtual void execute(const String& entityPerformingAction,
  		const std::vector<String>& entitiesBeingActedUpon,
  		const GameManager& gameManager) = 0;
};
#endif