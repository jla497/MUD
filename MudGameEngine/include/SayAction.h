#ifndef SAYACTION_H
#define SAYACTION_H
#include "Entity.h"
#include "GameManager.h"

//The SayAction class defines the behavior for when an player sends a message to every other player in the room.
class SayAction{
  public:
  	void execute(const String& entityPerformingAction,
  		const std::vector<String>& entitiesBeingActedUpon,
  		const GameManager& gameManager);
};
#endif