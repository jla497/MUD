
#include <iostream>
#include <memory>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

#include "actions/AttackAction.h"
#include "actions/LookAction.h"
#include "actions/MoveAction.h"
#include "actions/NullAction.h"
#include "actions/SayAction.h"
#include "commandparser/CommandParser.h"
#include "resources/commands.h"

namespace mudserver {
namespace commandparser {

using Tokenizer = boost::tokenizer<boost::char_separator<char>>;
using boost::algorithm::to_lower_copy;

using namespace resources::commands;

static std::unordered_map<std::string, ActKeyword> actionLookup = { // NOLINT
    {UNDEFINED, ActKeyword::undefined},
    {SAY, ActKeyword::say},
    {LOOK, ActKeyword::look},
    {ATTACK, ActKeyword::attack},
    {MOVE, ActKeyword::move}};

using ActionGenerator = std::unique_ptr<Action> (*)(PlayerCharacter &,
                                                    std::vector<std::string> &,
                                                    gamemanager::GameManager &);

template <typename T,
          typename = std::enable_if<std::is_base_of<Action, T>::value>>
std::unique_ptr<Action> generator(PlayerCharacter &pc,
                                  std::vector<std::string> &args,
                                  gamemanager::GameManager &manager) {
    return std::make_unique<T>(pc, args, manager);
};

const static std::vector<ActionGenerator> actionGenerators = {
    // NOLINT
    &generator<NullAction>, // undefined
    &generator<SayAction>,  &generator<LookAction>,
    &generator<MoveAction>, &generator<AttackAction>,
};

std::unique_ptr<Action>
CommandParser::actionFromPlayerCommand(PlayerCharacter &character,
                                       StrView command,
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

    auto index =
        static_cast<std::vector<ActionGenerator>::size_type>(actionType);
    if (index >= actionGenerators.size()) {
        return nullptr;
    }
    return actionGenerators[index](character, remainderOfTokens, gameManager);
}

} // namespace commandparser
} // namespace mudserver
