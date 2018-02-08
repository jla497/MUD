#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/format.hpp>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "actions/LookAction.h"
#include "logging.h"
// #include "resources/ActionMessages.h"

using boost::algorithm::join;
// namespace actmess = mudserver::resources::actions;

static auto logger = mudserver::logging::getLogger("LookAction");

LookAction *LookAction::clone() { return new LookAction(*this); }

void LookAction::execute_impl() {

    logger->debug("LookAction::Start");

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
        logger->debug("LookAction::Looking at room");
        // default: player looking at room
        std::string roomName = characterCurrentRoom->getName();
        std::vector<std::string> roomDesc = characterCurrentRoom->getDesc();
        std::vector<std::string> roomDirs = characterCurrentRoom->getDirs();

        auto chDescs = getDescriptionOfCharactersInRoom(characterCurrentRoom);
        auto objDescs = getDescriptionOfObjectsInRoom(characterCurrentRoom);
        std::string roomDescs = join(roomDesc, " ");
        std::string roomExits = join(roomDirs, " ");

        gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(),
            boost::str(
                boost::format{"%s: %s\n%s: %s\n%s: %s\n%s:\n %s\n%s:\n %s"} %
                "Room Name" % roomName % "Description" % roomDescs % "Exits" %
                roomExits % "Characters" % chDescs % "Objects in the room" %
                objDescs));
        logger->debug("Looking at room ::End");

    } else if (actionArguments.size() == MAX_LOOK_ARGS) {

        gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(),
            getDescriptionOfTargetCharacter(actionArguments.front(),
                                            characterCurrentRoom));
    } else {
        // too many objects to look at, error message to player
        gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(),
            "Please type /'look/' or /'look <object>/'");
    }

    logger->debug("LookAction::End");
}

std::string
LookAction::getDescriptionOfCharactersInRoom(RoomEntity *characterCurrentRoom) {
    logger->debug("getDescriptionOfCharactersInRoom::Start");
    auto &gameState = gameManager.getState();
    auto characterIds = gameState.getCharactersInRoom(characterCurrentRoom);
    std::vector<std::string> characterDescs{};
    std::vector<std::string> objectDescs{};

    for (auto &id : characterIds) {
        auto ch = gameState.getCharacterFromLUT(id);
        auto chId = std::to_string(id.getId());
        auto desc = ch->getShortDesc();
        auto longDesc = getStringFromStringVector(ch->getLongDesc());
        auto objects = ch->getObjects();
        std::string objDesc{};
        for (auto &obj : objects) {
            // TODO: do all objects have longDesc?
            objDesc += (obj.second.getShortDesc()) + "\n";
        }
        characterDescs.push_back(chId + ": " + desc + "\n" + longDesc + "\n\t" +
                                 desc + "'s objects: " + objDesc + "\n");
    }
    logger->debug("getDescriptionOfCharactersInRoom::joining characterDescs");
    std::string chDescs = join(characterDescs, " ");
    logger->debug("getDescriptionOfCharactersInRoom::End");
    return chDescs;
}

std::string
LookAction::getDescriptionOfObjectsInRoom(RoomEntity *characterCurrentRoom) {
    logger->debug("getDescriptionOfObjectsInRoom::Start");
    auto objects = characterCurrentRoom->getObjects();
    std::vector<std::string> objectDescs{};
    for (auto &obj : objects) {
        auto desc = getStringFromStringVector(obj.second.getLongDesc());
        // TODO: do all objects have longDesc?
        // auto desc = (obj.second.getShortDesc());
        objectDescs.push_back(desc + "\n");
    }
    std::string objDescs = join(objectDescs, " ");
    logger->debug("getDescriptionOfObjectsInRoom::End");
    return objDescs;
}

std::string
LookAction::getDescriptionOfTargetCharacter(std::string nameOfTarget,
                                            RoomEntity *characterCurrentRoom) {

    logger->debug("getDescriptionOfTargetCharacter::Start");
    if (nameOfTarget.empty()) {
        return "";
    }
    auto &gameState = gameManager.getState();
    auto characterIds = gameState.getCharactersInRoom(characterCurrentRoom);
    if (characterIds.empty()) {
        return nameOfTarget + " not found";
    }
    for (auto characterID : characterIds) {
        auto currentEntity = gameState.getCharacterFromLUT(characterID);
        if (!currentEntity) {
            continue;
        }
        auto shortDescOfCurrentCharacter = currentEntity->getShortDesc();
        if (boost::to_lower_copy(shortDescOfCurrentCharacter) ==
            boost::to_lower_copy(nameOfTarget)) {

            return getStringFromStringVector(currentEntity->getDesc());
        }
    }
    logger->debug("getDescriptionOfTargetCharacter::End");
    return "cannot see " + nameOfTarget;
}

std::string
LookAction::getStringFromStringVector(std::vector<std::string> stringVector) {
    std::string output = "";
    for (const auto &desc : stringVector) {
        logger->debug(desc);
        output += desc + "\n";
    }
    return output;
}
