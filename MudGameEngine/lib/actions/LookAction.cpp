#include <boost/algorithm/string/join.hpp>
#include <boost/format.hpp>
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "actions/LookAction.h"
#include "logging.h"
// #include "resources/ActionMessages.h"

using boost::algorithm::join;
// namespace actmess = mudserver::resources::actions;

std::unique_ptr<Action> LookAction::clone() const {
    return std::make_unique<LookAction>(*this);
}

void LookAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("LookAction::execute");

    auto &gameState = gameManager.getState();

    // get the room the player is in
    // TODO: Feel like this error checking could be rolled into the
    //       getCharacterLocation method?
    auto characterCurrentRoom =
        gameState.getCharacterLocation(*characterPerformingAction);
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

        auto chDescs = getCharacterDescriptions(characterCurrentRoom);
        auto objDescs = getObjectDescriptions(characterCurrentRoom);
        std::string roomDescs = join(roomDesc, " ");
        std::string roomExits = join(roomDirs, " ");

        gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(),
            boost::str(
                boost::format{"%s: %s\n%s: %s\n%s: %s\n%s:\n %s\n%s:\n %s"} %
                "Room Name" % roomName % "Description" % roomDescs % "Exits" %
                roomExits % "Characters" % chDescs % "Objects in the room" %
                objDescs));

    } else if (actionArguments.size() == MAX_LOOK_ARGS) {
        // TODO: show the description field when you look at a specific
        // character
        // TODO: look at object
        // Can you look at players?
        gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(),
            "looked at object " + actionArguments.front());
    } else {
        // too many objects to look at, error message to player
        gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(),
            "Please type /'look/' or /'look <object>/'");
    }
}

std::string
LookAction::getCharacterDescriptions(RoomEntity *characterCurrentRoom) {
    // TODO: when you look at a room the characters longdescs should be
    // displayed
    auto &gameState = gameManager.getState();
    auto characterIds = gameState.getCharactersInRoom(characterCurrentRoom);
    std::vector<std::string> characterDescs{};
    std::vector<std::string> objectDescs{};

    for (auto &id : characterIds) {
        auto ch = gameState.getCharacterFromLUT(id);
        auto chId = std::to_string(id.getId());
        auto desc = ch->getShortDesc();
        auto objects = ch->getObjects();
        std::string objDesc{};
        for (auto &obj : objects) {
            objDesc += obj.second.getShortDesc() + "\n";
        }
        characterDescs.push_back(boost::str(boost::format{"%d: %s\n\t%s's objects: %s\n"} % chId % desc % desc % objDesc));
    }
    std::string chDescs = join(characterDescs, " ");
    return chDescs;
}

std::string
LookAction::getObjectDescriptions(RoomEntity *characterCurrentRoom) {
    auto objects = characterCurrentRoom->getObjects();
    std::vector<std::string> objectDescs{};
    for (auto &obj : objects) {
        auto desc = obj.second.getShortDesc();
        objectDescs.push_back(desc + "\n");
    }

    std::string objDescs = join(objectDescs, " ");
    return objDescs;
}