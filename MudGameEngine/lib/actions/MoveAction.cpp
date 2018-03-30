
#include "actions/MoveAction.h"
#include "logging.h"
#include <actions/LookAction.h>
#include <memory>
// #include "entities/CharacterEntity.h"
#include "entities/CombatComponent.h"

std::vector<std::string> MoveAction::moveLookup = {"north", "south", "east",
                                                   "west"};

std::unique_ptr<Action> MoveAction::clone() const {
    return std::make_unique<MoveAction>(*this);
}

void MoveAction::execute_impl() {
    static auto logger = mudserver::logging::getLogger("Action::MoveAction");

    // characters cannot move between rooms while they are in
    // combat  unless they use some sort of flee action)
    if (characterPerformingAction->getCombatComponent()->getCombatState() ==
        CombatStates::FIGHTING) {
        gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(),
            "You cannot leave the room, you are in Combat!");
        return;
    }

    std::string userinfo(
        "userid: " +
        std::to_string(characterPerformingAction->getEntityId().getId()));
    logger->info(userinfo);

    auto &gameState = gameManager.getState();
    RoomEntity *room =
        gameState.getCharacterLocation(*characterPerformingAction);

    if (!room) {
        logger->error("Character not found in any room...");
        return;
    }
    std::string roomInfo("roomid: " + std::to_string(room->getId()));
    logger->info(roomInfo);

    if (actionArguments.empty()) {
        logger->error("Not a valid move command...");
        gameManager.sendCharacterMessage(
            characterPerformingAction->getEntityId(),
            "Not a valid move command...");
        return;
    }

    auto cmd = actionArguments[0];

    boost::algorithm::to_lower(cmd);

    auto direction = std::find(moveLookup.begin(), moveLookup.end(), cmd);

    if (direction == moveLookup.end()) {
        logger->error("not a valid direction...");
        return;
    } else {

        // get next room id from current room

        auto nextRoomId = room->getDestRoomIdOf(*direction);

        // not a valid direction
        if (nextRoomId == RoomEntity::NO_ROOM_ID) {
            return;
        }

        logger->info("got nextRoomId...");
        // get nextroom
        auto nextRoom = gameState.getRoomFromLUT(nextRoomId);
        // Room with nextRoomId does not exist
        if (!nextRoom) {
            logger->warning("nextRoom is null...");
            return;
        }

        std::string nextRoomIdStr("next room id: " +
                                  std::to_string(nextRoom->getId()));
        logger->info(nextRoomIdStr);
        // move the playerCharacter from the current room to the next room
        auto characterId = characterPerformingAction->getEntityId().getId();

        room->removeEntity(characterId);

        nextRoom->addEntity(characterId);

        auto mCharacterPtr = characterPerformingAction;
        gameState.addCharacterRoomRelationToLUT(mCharacterPtr->getEntityId(),
                                                nextRoom->getId());

        LookAction{playerPerformingAction, {}, gameManager}.execute();

        logger->debug("MoveAction complete...");
        return;
    }
}
