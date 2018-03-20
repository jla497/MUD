
#include <actions/AttackAction.h>
#include <memory>
#include <ostream>
#include <string>
#include <type_traits>
#include <unordered_map>

#include "actions/AttackAction.h"
#include "actions/CharacterModAction.h"
#include "actions/DecoyAction.h"
#include "actions/HaltAction.h"
#include "actions/LookAction.h"
#include "actions/MoveAction.h"
#include "actions/NullAction.h"
#include "actions/PrgmAction.h"
#include "actions/SaveAction.h"
#include "actions/SayAction.h"
#include "actions/SpellAction.h"
#include "actions/SwapAction.h"
#include "actions/TimedAction.h"
#include "gamemanager/GameManager.h"
#include "logging.h"

// FIXME: this should possibly work on the enum keyword rather than the
// description string
std::unordered_map<std::string, bool> Action::isAdminAction = {
    {"Program action", true}, {"Save action", true}, {"Halt action", true}};

Action::Action(Player &playerPerformingAction,
               std::vector<std::string> actionArguments,
               mudserver::gamemanager::GameManager &gameManager)
    : playerPerformingAction{playerPerformingAction},
      actionArguments{std::move(actionArguments)}, gameManager{gameManager} {}

void Action::execute() {
    // check if this is an admin action
    static auto logger = mudserver::logging::getLogger("Action::Action");

    auto &playerService = gameManager.getPlayerService();
    auto characterId =
        playerService.playerToCharacter(playerPerformingAction.getId());
    characterPerformingAction =
        gameManager.getState().getCharacterFromLUT(*characterId);

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
        gameManager.addActionToQueue(clone());
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

template <typename T,
          typename = std::enable_if<std::is_base_of<Action, T>::value>>
static std::pair<std::string, std::unique_ptr<Action>> generatePair() {
    auto action = std::make_unique<T>();
    return {action->description(), std::move(action)};
}

void Action::registerAdminActions(const std::string &file) {
    std::unordered_map<std::string, std::unique_ptr<Action>> map = {
        generatePair<AttackAction>(), generatePair<CharacterModAction>(),
        generatePair<DecoyAction>(),  generatePair<HaltAction>(),
        generatePair<LookAction>(),   generatePair<MoveAction>(),
        generatePair<NullAction>(),   generatePair<PrgmAction>(),
        generatePair<SaveAction>(),   generatePair<SayAction>(),
        generatePair<SpellAction>(),  generatePair<SwapAction>(),
        generatePair<TimedAction>(),
    };

    auto root = YAML::LoadFile(file)["requires_admin"];
}
