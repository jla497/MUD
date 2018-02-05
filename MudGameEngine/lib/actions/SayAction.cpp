#include <string>
#include <vector>

#include "actions/SayAction.h"
#include "logging.h"

void SayAction::execute() {
    static auto logger = mudserver::logging::getLogger("SayAction::execute");
    logger->info("Entered SayAction");

	auto gameState = gameManager.getState();

    // get player who is saying the message
    auto playerSayingMessage = playerCharacter;
    auto playersMessageTokens = entitiesBeingActedUpon;
    if(playerSayingMessage == NULL){
        //output error (DEBUG LOG)
        logger->error("Player does not exist");
    	return;
    }

    //TODO: make ActionParser send the whole string, 
    //currently we are doing a lot of work right before executing the game logic,
    //it would be better to do this when the action is created.

    // get the message the player wants to send
    std::string messageSentByPlayer;
    for(auto const& stringToken : playersMessageTokens ){
        messageSentByPlayer += stringToken;
    }
    //auto messageSentByPlayer = playersMessageTokens.at(0);

    if(messageSentByPlayer.empty()){
        //do nothing on an empty messsage
        return;
    }

    //--get the room the player is in
    auto roomPlayerIsIn = gameState.getCharacterLocation(playerSayingMessage);
    if(roomPlayerIsIn == nullptr){
        logger->error("roomPlayerIsIn does not exist");
    }

    //--get list of players in the room
    auto IDsOfPlayersInRoom = gameState.getCharactersInRoom(roomPlayerIsIn);
    auto sayingPlayersId = playerSayingMessage->getEntityId().getId();

    //--send the message to all the players except the one who sent it
    for(auto characterID : IDsOfPlayersInRoom){
        if(characterID.getId() != sayingPlayersId){
            gameManager.sendCharacterMessage(characterID,
                playerSayingMessage->getShortDesc() + " says: " + messageSentByPlayer
                );

        }
    }   
}
