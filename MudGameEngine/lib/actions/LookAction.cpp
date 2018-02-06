#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <boost/algorithm/string/join.hpp>
#include <boost/format.hpp>

#include "actions/LookAction.h"
#include "logging.h"
// #include "resources/ActionMessages.h"

using boost::algorithm::join;
// namespace actmess = mudserver::resources::actions;

void LookAction::execute() {
    static auto logger = mudserver::logging::getLogger("LookAction::execute");

    auto& gameState = gameManager.getState();

    // get the room the player is in
    // TODO: Feel like this error checking could be rolled into the 
    //       getCharacterLocation method?
    auto characterCurrentRoom =
        gameState.getCharacterLocation(&characterPerformingAction);
    if (!characterCurrentRoom) {
        logger->error(
            "Character is not in a room! Suspect incorrect world init");
        // return early, as we are in a bad state - the player is not in a room!
        return;
    }
    
    if (actionArguments.empty()) {
        // default: player looking at room
        auto roomName = characterCurrentRoom->getName();
        auto roomDesc = characterCurrentRoom->getDesc();
        std::vector<std::string> roomDirs = characterCurrentRoom->getDirs();
        std::string roomExits = join(roomDirs, " ");

        // gameManager.sendCharacterMessage(
        //     characterPerformingAction.getEntityId(),
        //     boost::str(boost::format{"%s: %s\n%s: %s\n%s: %s"} %
        //                    "Room Name" % roomName %
        //                    "Description" % roomDesc %
        //                    "Exits" % roomExits));

         gameManager.sendCharacterMessage(
            characterPerformingAction.getEntityId(), "looked at room");

    } else if (actionArguments.size() == MAX_LOOK_ARGS){
        // look at object        
        gameManager.sendCharacterMessage(
            characterPerformingAction.getEntityId(),
            "looked at object " + actionArguments.front());
    } else {
        // too many objects to look at, error message to player
        gameManager.sendCharacterMessage(
            characterPerformingAction.getEntityId(),
            "Please type /'look/' or /'look <object>/'");
    }


    // TODO: can players "look" at players?
    //--get list of players in the room
    // auto characterIdsInRoom =
    //     gameState.getCharactersInRoom(characterCurrentRoom);
    // if (characterIdsInRoom.empty()) {
    //     logger->debug("There are no characters in the room, exiting");
    //     return;
    // }

}
