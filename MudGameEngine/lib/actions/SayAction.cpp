#include <string>
#include <vector>
#include <numeric>
#include <sstream>

#include "actions/SayAction.h"
#include "logging.h"

void SayAction::execute() {
    static auto logger = mudserver::logging::getLogger("SayAction::execute");

    auto& gameState = gameManager.getState();

    // get player who is saying the message
    auto playerSayingMessage = characterPerformingAction;
    auto playersMessageTokens = entitiesBeingActedUpon;


    //TODO: make CommandParser send the whole string,
    //currently we are doing a lot of work right before executing the game logic,
    //it would be better to do this when the action is created.

    // get the message the player wants to send
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

    //--get the room the player is in
    auto characterCurrentRoom =
        gameState.getCharacterLocation(&playerSayingMessage);
    if (!characterCurrentRoom) {
        logger->error("characterCurrentRoom does not exist");

        // return early, as we are in a bad state - the player is not in a room!
        return;
    }

    auto roomDesc = characterCurrentRoom->getDesc();

    //--get list of players in the room
    auto characterIdsInRoom = gameState.getCharactersInRoom(characterCurrentRoom);
    if(characterIdsInRoom.empty()){
        logger->debug("There are no characters in the room, exiting");
        return;
    }

    auto speakingCharacterDesc = playerSayingMessage.getShortDesc();

    //--send the message to all the players except the one who sent it
    for(auto characterID : characterIdsInRoom){
        gameManager.sendCharacterMessage(
            characterID, speakingCharacterDesc + ": " + messageSentByPlayer);
    }
}
