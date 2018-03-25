#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

#include "actions/AttackAction.h"
#include "actions/CharacterModAction.h"
#include "actions/HaltAction.h"
#include "actions/LookAction.h"
#include "actions/MoveAction.h"
#include "actions/NullAction.h"
#include "actions/PrgmAction.h"
#include "actions/SaveAction.h"
#include "actions/SayAction.h"
#include "actions/SwapAction.h"
#include "actions/TimedAction.h"
#include "commandparser/CommandParser.h"
#include "resources/commands.h"

namespace mudserver {
namespace commandparser {

using Tokenizer = boost::tokenizer<boost::char_separator<char>>;
using boost::algorithm::to_lower_copy;

using namespace resources::commands;

static std::unordered_map<std::string, ActKeyword> actionLookup =
    { // NOLINT
        {UNDEFINED, ActKeyword::undefined},
        {SAY, ActKeyword::say},
        {LOOK, ActKeyword::look},
        {ATTACK, ActKeyword::attack},
        {MOVE, ActKeyword::move},
        {PROGRAM, ActKeyword::program},
        {TIMED, ActKeyword::timed},
        {SAVE, ActKeyword::save},
        {CHARMOD, ActKeyword::charmod},
        {HALT, ActKeyword::halt},
        {SWAP, ActKeyword::swap}};

using ActionGenerator = std::unique_ptr<Action> (*)(Player &,
                                                    std::vector<std::string> &,
                                                    gamemanager::GameManager &);

template <typename T,
          typename = std::enable_if<std::is_base_of<Action, T>::value>>
std::unique_ptr<Action> generator(Player &player,
                                  std::vector<std::string> &args,
                                  gamemanager::GameManager &manager) {
    return std::make_unique<T>(player, args, manager);
};

// FIXME: this should be an unordered_map, but some people don't have a
// std::hash  specialization for enums in their old gcc/glibc
const static std::map<ActKeyword, ActionGenerator> actionGenerators = {
    // NOLINT
    {ActKeyword::undefined, &generator<NullAction>},
    {ActKeyword::say, &generator<SayAction>},
    {ActKeyword::look, &generator<LookAction>},
    {ActKeyword::attack, &generator<AttackAction>},
    {ActKeyword::move, &generator<MoveAction>},
    {ActKeyword::program, &generator<PrgmAction>},
    {ActKeyword::timed, &generator<TimedAction>},
    {ActKeyword::save, &generator<SaveAction>},
    {ActKeyword::charmod, &generator<CharacterModAction>},
    {ActKeyword::halt, &generator<HaltAction>},
    {ActKeyword::swap, &generator<SwapAction>}};

std::unique_ptr<Action>
CommandParser::actionFromPlayerCommand(Player &player, StrView command,
                                       gamemanager::GameManager &gameManager) {

    Tokenizer tokens{command};
    auto tokenIterator = tokens.begin();
    auto actionTypeIter = actionLookup.find(to_lower_copy(*tokenIterator));

    std::stringstream tokenRep;
    std::vector<std::string> remainderOfTokens(++tokenIterator, tokens.end());
    std::copy(remainderOfTokens.begin(), remainderOfTokens.end(),
              std::ostream_iterator<std::string>(tokenRep, ", "));

    ActKeyword actionType = (actionTypeIter == actionLookup.end())
                                ? ActKeyword::undefined
                                : actionTypeIter->second;

    return actionGenerators.at(actionType)(player, remainderOfTokens,
                                           gameManager);
}

std::pair<UsernameType, PasswordType>
CommandParser::identifiersFromIdentifyCommand(StrView command) {
    Tokenizer tokens{command};
    auto tokenIterator = tokens.begin();

    if (to_lower_copy(*tokenIterator++) != IDENTIFY) {
        return std::make_pair("", "");
    }

    return std::make_pair(*tokenIterator++, *tokenIterator);
}

} // namespace commandparser
} // namespace mudserver
