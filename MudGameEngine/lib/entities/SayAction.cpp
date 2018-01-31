#include <string>
#include <vector>
#include "SayAction.h"
#include "GameManager.h"


SayAction::execute(const String& entityPerformingAction,
  		const std::vector<String>& entitiesBeingActedUpon,
  		const GameManager& gameManager){
	//get player who is saying the message
		//--likely first param

	//get the message the player wants to send
		//--likely first index in the string vector

	//get the players who will get the message
		//--get the room the player is in
		//--get list of players in the room
		//--send the message to all the players except the one who sent it
}
