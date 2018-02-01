#ifndef SAYACTION_H
#define SAYACTION_H

#include "Action.h"
#include "gamemanager/GameManager.h"

//The SayAction class defines the behavior for when an player sends a message to every other player in the room.
class SayAction : public Action{
  public:
  	SayAction(const std::string& entityPerformingAction,
  		const std::vector<std::string>* entitiesBeingActedUpon,
  		const mudserver::gamemanager::GameManager& gameManager);

  	void execute();
};
#endif