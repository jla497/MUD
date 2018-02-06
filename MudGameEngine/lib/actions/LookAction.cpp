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
        // TODO: should it show list of npc and objects too?
        std::string roomName = characterCurrentRoom->getName();
        std::vector<std::string> roomDesc = characterCurrentRoom->getDesc();
        std::vector<std::string> roomDirs = characterCurrentRoom->getDirs();
        std::string roomDescs = join(roomDesc, " ");
        std::string roomExits = join(roomDirs, " ");

        gameManager.sendCharacterMessage(
            characterPerformingAction.getEntityId(),
            boost::str(boost::format{"%s: %s\n%s: %s\n%s: %s"} %
                           "Room Name" % roomName %
                           "Description" % roomDescs %
                           "Exits" % roomExits));

    } else if (actionArguments.size() == MAX_LOOK_ARGS){
        // TODO: look at object        
        // Can you look at players?
        gameManager.sendCharacterMessage(
            characterPerformingAction.getEntityId(),
            "looked at object " + actionArguments.front());
    } else {
        // too many objects to look at, error message to player
        gameManager.sendCharacterMessage(
            characterPerformingAction.getEntityId(),
            "Please type /'look/' or /'look <object>/'");
    }



}