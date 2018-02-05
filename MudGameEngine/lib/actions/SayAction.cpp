#include <string>
#include <vector>
#include <numeric>
#include <sstream>

#include "actions/SayAction.h"
#include "logging.h"

void SayAction::execute() {
    static auto logger = mudserver::logging::getLogger("SayAction::execute");
    logger->debug("Entered SayAction");

    auto& gameState = gameManager.getState();

    // get player who is saying the message
    auto playerSayingMessage = this->characterPerformingAction;
    auto playersMessageTokens = this->entitiesBeingActedUpon;


    //TODO: make CommandParser send the whole string,
    //currently we are doing a lot of work right before executing the game logic,
    //it would be better to do this when the action is created.

    // get the message the player wants to send
    logger->debug("Starting creating message string:");
    std::ostringstream stringStream;
    for(auto const& stringToken : playersMessageTokens){
        stringStream << stringToken << " ";
    }

    auto messageSentByPlayer = stringStream.str();
    if(messageSentByPlayer.empty()){
        //do nothing on an empty messsage
        logger->debug("message is empty (early exit)");
        return;
    }
    logger->debug("Created message string:");
    logger->debug(messageSentByPlayer);


    logger->debug("Get players room");
    //--get the room the player is in
    auto roomPlayerIsIn = gameState.getCharacterLocation(std::addressof(playerSayingMessage));
    if(roomPlayerIsIn == nullptr || roomPlayerIsIn == NULL){
        logger->error("roomPlayerIsIn does not exist");
    }
    logger->debug("Finished: Get players room");

    logger->debug("try to acess room member var");
    auto roomDesc = roomPlayerIsIn->getDesc();
    logger->debug("Done: try to acess room member var");

    logger->debug("Start: get ids of characters in room");
    //--get list of players in the room
    auto IDsOfPlayersInRoom = gameState.getCharactersInRoom(roomPlayerIsIn);
    if(IDsOfPlayersInRoom.empty()){
        logger->error("Either the room does not exist or there are no characters in the room");
    }
    logger->debug("Finished: get characters in room");
    logger->debug("Start: get Id of saying player");
    auto sayingPlayersId = playerSayingMessage.getEntityId().getId();
    logger->debug("Finish: get Id of saying player");
    logger->debug("Start: get saying players description");
    auto sayingPlayersShortDesc = playerSayingMessage.getShortDesc();
    logger->debug("Finish: get saying players description");


    //--send the message to all the players except the one who sent it
    for(auto characterID : IDsOfPlayersInRoom){
        logger->info("calling gameManager.sendCharacterMessage()");
        //if(characterID.getId() != sayingPlayersId){
            gameManager.sendCharacterMessage(characterID,
                sayingPlayersShortDesc + ": " + messageSentByPlayer
                );
      //  }
    }


    logger->debug("Exiting SayAction");

}
