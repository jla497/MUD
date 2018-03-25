#include <memory>
#include <ostream>

#include "actions/Action.h"
#include "gamemanager/GameManager.h"
#include "logging.h"
#include "controllers/CharacterController.h"

// FIXME: this should possibly work on the enum keyword rather than the
// description string
std::unordered_map<std::string, bool> Action::isAdminAction = {
    {"Program action", true}, {"Save action", true}, {"Halt action", true}};

Action::Action(CharacterController &controller,
               std::vector<std::string> actionArguments,
               mudserver::gamemanager::GameManager &gameManager)
    : controller(controller), playerPerformingAction{*(controller.getPlayer())},
      actionArguments{std::move(actionArguments)}, gameManager{gameManager},
characterPerformingAction(controller.getCharacter()){}

void Action::execute() {
    // check if this is an admin action
    static auto logger = mudserver::logging::getLogger("Action::Action");

//    auto &playerService = gameManager.getPlayerService();
//    auto characterId =
//        playerService.playerToCharacter(playerPerformingAction.getId());
//    if(characterId){
//        characterPerformingAction =
//                gameManager.getState().getCharacterFromLUT(*characterId);
//    }

    // check if action is admin action and if character has an administrator
    // role
    if (Action::isAdminAction[description()]) {
        if (playerPerformingAction.hasAdminPrivilege()) {
            execute_impl();
        } else {
            logger->warning("Player " + playerPerformingAction.getUsername() +
                            " is not an admin, but tried to perform " +
                            this->description());
        }
    } else {
        execute_impl();
    }

    if (timeRemaining > 0) {
        timeRemaining--;
        auto newAction = clone();
        auto ptr = std::unique_ptr<Action>(newAction);
        gameManager.addActionToQueue(std::move(ptr));
    }
}
std::ostream &operator<<(std::ostream &os, const Action &action) {
    os << action.description() << ", [";
    for (const auto &entity : action.actionArguments) {
        os << entity << ", ";
    }
    os << "]" << std::endl;
    return os;
}

CharacterEntity* Action::getPerformingEntity() {
    return characterPerformingAction;
}
std::vector<std::string> Action::getArgs() {
    return actionArguments;
}
