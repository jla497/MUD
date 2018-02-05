#include <string>
#include <vector>

#include "actions/SayAction.h"

void SayAction::execute() {
	auto gameState = gameManager.getState();

    // get player who is saying the message
    auto playerSayingMessage = playerCharacter;
    if(playerSayingMessage == NULL){
    	//output error (DEBUG LOG)
    	return;
    }

    // get the message the player wants to send
    auto messageSentByPlayer = entitiesBeingActedUpon.at(0);
    if(messageSentByPlayer.empty()){
        //do nothing on an empty messsage
        return;
    }

    //--get the room the player is in
    auto roomPlayerIsIn = gameState.getCharacterLocation(playerSayingMessage);
    //--get list of players in the room
    auto IDsOfPlayersInRoom = gameState.getCharactersInRoom(roomPlayerIsIn);
    auto sayingPlayersId = playerSayingMessage->getEntityId().getId();

    //--send the message to all the players except the one who sent it
    for(auto characterID : IDsOfPlayersInRoom){
        if(characterID->getId() != sayingPlayersId){
            gameManager.sendCharacterMessage(characterID,
                playerSayingMessage->getShortDesc() + " says: " + messageSentByPlayer
                );

        }
    }   
}


