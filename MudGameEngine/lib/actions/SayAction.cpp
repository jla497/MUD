#include <string>
#include <vector>
#include <numeric>
#include <sstream>

#include "actions/SayAction.h"
#include "logging.h"

void SayAction::execute() {
    static auto logger = mudserver::logging::getLogger("SayAction::execute");
    logger->info("Entered SayAction");

    auto& gameState = gameManager.getState();

    // get player who is saying the message
    auto playerSayingMessage = this->characterPerformingAction;
    auto playersMessageTokens = this->entitiesBeingActedUpon;

    //TODO: make CommandParser send the whole string, 
    //currently we are doing a lot of work right before executing the game logic,
    //it would be better to do this when the action is created.

    // get the message the player wants to send
    std::ostringstream stringStream;
    for(auto const& stringToken : playersMessageTokens){
        stringStream << stringToken;
    }

    auto messageSentByPlayer = stringStream.str();
    if(messageSentByPlayer.empty()){
        //do nothing on an empty messsage
        return;
    }

    //--get the room the player is in
    auto roomPlayerIsIn = gameState.getCharacterLocation(&playerSayingMessage);
    if(roomPlayerIsIn == nullptr){
        logger->error("roomPlayerIsIn does not exist");
    }

    //--get list of players in the room
    auto IDsOfPlayersInRoom = gameState.getCharactersInRoom(roomPlayerIsIn);
    auto sayingPlayersId = playerSayingMessage.getEntityId().getId();
    auto sayingPlayersShortDesc = playerSayingMessage.getShortDesc();

    //--send the message to all the players except the one who sent it
    for(auto characterID : IDsOfPlayersInRoom){
        logger->info("calling gameManager.sendCharacterMessage()");
        //if(characterID.getId() != sayingPlayersId){
            gameManager.sendCharacterMessage(characterID,
                sayingPlayersShortDesc + ": " + messageSentByPlayer
                );


      //  }
    }


    logger->info("Exiting SayAction");

}
