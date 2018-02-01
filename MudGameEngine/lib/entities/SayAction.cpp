#include <string>
#include <vector>
#include "SayAction.h"

void SayAction::execute(){
	//get player who is saying the message
		//--likely first param

	//get the message the player wants to send
		//--likely first index in the string vector

	//get the players who will get the message
		//--get the room the player is in
		//--get list of players in the room
		//--send the message to all the players except the one who sent it
}

  SayAction::SayAction(const std::string& entityPerformingAction,
  		const std::vector<std::string>* entitiesBeingActedUpon,
  		const mudserver::gamemanager::GameManager& gameManager) 
  		: Action(const std::string& entityPerformingAction,
  		const std::vector<std::string>* entitiesBeingActedUpon,
  		const mudserver::gamemanager::GameManager& gameManager){


  			

  		}

   		