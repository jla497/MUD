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

#include "commandparser/CommandParser.h"
#include "resources/commands.h"

namespace mudserver {
namespace commandparser {

using Tokenizer = boost::tokenizer<boost::char_separator<char>>;
using boost::algorithm::to_lower_copy;

using namespace resources::commands;

static auto actionLookup =
    ([]() -> std::unordered_map<std::string, ActKeyword> { // NOLINT
        std::unordered_map<std::string, ActKeyword> ret{
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
        if (ret.size() != static_cast<std::size_t>(ActKeyword::_N_ACTIONS_)) {
            std::cerr << "You've added an ActKeyword but not added it to the "
                         "map in commandparser.cpp. Fix it. Terminating.\n";
            std::terminate();
        }
        return ret;
    })();

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

    return Action::base(actionType)
        ->clone(player, remainderOfTokens, gameManager);
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
