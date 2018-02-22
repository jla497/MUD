#include <boost/algorithm/string/join.hpp>
#include <boost/format.hpp>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "actions/SayAction.h"
#include "logging.h"
#include "resources/ActionMessages.h"

using boost::algorithm::join;
namespace actmess = mudserver::resources::actions;

void SayAction::execute() {
    static auto logger = mudserver::logging::getLogger("SayAction::execute");

    auto &gameState = gameManager.getState();

    // get player who is saying the message
    auto playerSayingMessage = characterPerformingAction;

    //--get the room the player is in
    auto characterCurrentRoom =
        gameState.getCharacterLocation(&playerSayingMessage);
    if (!characterCurrentRoom) {
        logger->error(
            "Character is not in a room! Suspect incorrect world init");
        // return early, as we are in a bad state - the player is not in a room!
        return;
    }

    std::string messageSentByPlayer;
    if (actionArguments.empty()) {
        messageSentByPlayer = actmess::SPEECHLESS;
    } else {
        messageSentByPlayer = join(actionArguments, " ");
    }

    //--get list of players in the room
    auto characterIdsInRoom =
        gameState.getCharactersInRoom(characterCurrentRoom);
    if (characterIdsInRoom.empty()) {
        logger->debug("There are no characters in the room, exiting");
        return;
    }

    auto speakingCharacterDesc = playerSayingMessage.getShortDesc();
    auto speakingCharacterId = playerSayingMessage.getEntityId();

    // send the message to all the players in the room
    for (auto characterID : characterIdsInRoom) {
        gameManager.sendCharacterMessage(
            characterID, boost::str(boost::format{"%s: %s"} %
                                    (speakingCharacterId == characterID
                                         ? "You"
                                         : speakingCharacterDesc) %
                                    messageSentByPlayer));
    }
}
