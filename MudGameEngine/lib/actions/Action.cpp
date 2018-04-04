
#include <memory>
#include <ostream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "actions/Action.h"
#include "actions/AttackAction.h"
#include "actions/CastAction.h"
#include "actions/CharacterModAction.h"
#include "actions/DecoyAction.h"
#include "actions/HaltAction.h"
#include "actions/LookAction.h"
#include "actions/MoveAction.h"
#include "actions/NullAction.h"
#include "actions/PrgmAction.h"
#include "actions/SaveAction.h"
#include "actions/SayAction.h"
#include "actions/SwapAction.h"
#include "actions/TakeAction.h"
#include "actions/TimedAction.h"
#include "controllers/CharacterController.h"
#include "gamemanager/GameManager.h"
#include "logging.h"
#include "observe/ActionObserver.h"
#include "observe/Observable.h"

using UActKeyword = std::underlying_type_t<ActKeyword>;

// can't have it static in makeBase because makeBase is templated
static UActKeyword baseIndex() {
    static UActKeyword index = 0;
    return index++;
}

template <typename T,
          typename = std::enable_if<std::is_base_of<Action, T>::value>>
static std::unique_ptr<Action> makeBase(ActKeyword keyword) {
    if (static_cast<UActKeyword>(keyword) != baseIndex()) {
        // this is not a state we want to be running under
        std::cerr << "Actions are out of order. Fix the ordering in "
                     "action.cpp. Terminating.\n";
        std::terminate();
    }
    return std::make_unique<T>();
}

const Action *Action::base(ActKeyword keyword) {
    static auto bases = ([]() -> std::vector<std::unique_ptr<Action>> {
        // constructing a vector<unique_ptr<T>> is very fiddly. this is a hack
        // to make it work
        std::unique_ptr<Action> array[] = {
            makeBase<NullAction>(ActKeyword::undefined),
            makeBase<SayAction>(ActKeyword::say),
            makeBase<LookAction>(ActKeyword::look),
            makeBase<AttackAction>(ActKeyword::attack),
            makeBase<MoveAction>(ActKeyword::move),
            makeBase<PrgmAction>(ActKeyword::program),
            makeBase<TimedAction>(ActKeyword::timed),
            makeBase<SaveAction>(ActKeyword::save),
            makeBase<CharacterModAction>(ActKeyword::charmod),
            makeBase<HaltAction>(ActKeyword::halt),
            makeBase<SwapAction>(ActKeyword::swap),
            makeBase<CastAction>(ActKeyword::cast),
            makeBase<DecoyAction>(ActKeyword::decoy),
            makeBase<TakeAction>(ActKeyword::take)};
        std::vector<std::unique_ptr<Action>> ret{
            std::make_move_iterator(std::begin(array)),
            std::make_move_iterator(std::end(array))};
        if (ret.size() != static_cast<std::size_t>(ActKeyword::_N_ACTIONS_)) {
            std::cerr << "You've added an ActKeyword but not added it to the "
                         "vector in action.cpp. Fix it. Terminating.\n";
            std::terminate();
        }
        return ret;
    })();
    assert(keyword < ActKeyword::_N_ACTIONS_);
    return bases[static_cast<std::size_t>(keyword)].get();
}

bool Action::requiresAdmin() const { return isAdmin; }

void Action::setAdmin(bool admin) const { isAdmin = admin; }

std::unique_ptr<Action>
Action::clone(CharacterController &controller,
              std::vector<std::string> actionArguments,
              mudserver::gamemanager::GameManager &gameManager) const {
    auto ret = clone();
    ret->initialize(controller, std::move(actionArguments), gameManager);
    return ret;
}

void Action::initialize(CharacterController &controller,
                        std::vector<std::string> actionArguments,
                        mudserver::gamemanager::GameManager &gameManager) {
    this->controller = &controller;
    this->playerPerformingAction = controller.getPlayer();
    this->gameManager = &gameManager;
    this->actionArguments = std::move(actionArguments);
}

inline void assertNotBase(const Action *action) {
#ifndef NDEBUG
    for (int k = 0; k < static_cast<int>(ActKeyword::_N_ACTIONS_); k++) {
        assert(action != Action::base(static_cast<ActKeyword>(k)));
    }
#endif
}

void Action::execute() {
    assertNotBase(this);
    // also check that they didn't do something like
    // Action::base(keyword)->clone();
    assert(playerPerformingAction != nullptr && gameManager != nullptr);

    // check if this is an admin action
    static auto logger = mudserver::logging::getLogger("Action::Action");

    auto &playerService = gameManager->getPlayerService();
    auto characterId =
        playerService.playerToCharacter(playerPerformingAction->getId());
    characterPerformingAction =
        gameManager->getState().getCharacterFromLUT(*characterId);

    // check if action is admin action and if character has an administrator
    // role
    if (isAdmin) {
        if (playerPerformingAction->hasAdminPrivilege()) {

            execute_impl();
        } else {
            logger->warning("Player " + playerPerformingAction->getUsername() +
                            " is not an admin, but tried to perform " +
                            this->description());
        }
    } else {
        execute_impl();
    }

    if (timeRemaining > 0) {
        timeRemaining--;
        gameManager->addActionToQueue(clone());
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

#define generatePair(keyword)                                                  \
    { #keyword, ActKeyword::keyword }

void Action::registerAdminActions(const std::string &file) {
    static auto map = ([]() -> std::unordered_map<std::string, ActKeyword> {
        std::unordered_map<std::string, ActKeyword> ret{
            generatePair(undefined), generatePair(say),  generatePair(look),
            generatePair(attack),    generatePair(move), generatePair(program),
            generatePair(timed),     generatePair(save), generatePair(charmod),
            generatePair(halt),      generatePair(swap), generatePair(cast),
            generatePair(decoy),     generatePair(take)};
        if (ret.size() != static_cast<std::size_t>(ActKeyword::_N_ACTIONS_)) {
            std::cerr << "You've added an ActKeyword but not added it to the "
                         "admin map in action.cpp. Fix it. Terminating.\n";
            std::terminate();
        }
        return ret;
    })();

    auto root = YAML::LoadFile(file)["requires_admin"];
    for (const auto &pair : map) {
        const auto &node = root[pair.first];
        if (node.IsDefined()) {
            auto admin = node.as<bool>();
            Action::base(pair.second)->setAdmin(admin);
        }
    }
}

#undef generatePair
CharacterEntity *Action::getPerformingEntity() {
    return characterPerformingAction;
}
std::vector<std::string> Action::getArgs() { return actionArguments; }

void Action::accept(ActionObserver *observer) {}
