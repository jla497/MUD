#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <sstream>

#include "commandparser/CommandParser.h"
#include "resources/commands.h"

namespace mudserver {
namespace commandparser {

using Tokenizer = boost::tokenizer<boost::char_separator<char>>;
using boost::algorithm::to_lower_copy;

using namespace resources::commands;

std::unordered_map<std::string, ActKeyword> CommandParser::actionLookup = {
    {SAY, ActKeyword::say},
    {LOOK, ActKeyword::look},
    {ATTACK, ActKeyword::attack},
    {MOVE, ActKeyword::move}};

CommandParser::CommandParser() {}

std::string CommandParser::actionFromPlayerCommand(gamemanager::Character* character,
                                                   StrView command) {
    Tokenizer tokens{command};

    auto tokenIterator = tokens.begin();

    auto actionTypeIter = actionLookup.find(to_lower_copy(*tokenIterator));

    std::vector<std::string> remainderOfTokens{};
    std::stringstream tokenRep;
    for (++tokenIterator; tokenIterator != tokens.end(); ++tokenIterator) {
        // choosing not to lowercase remainder of tokens as some commands may
        // wish to retain user formatting
        remainderOfTokens.push_back(*tokenIterator);
        tokenRep << *tokenIterator << ", ";
    }

    ActKeyword actionType;
    if (actionTypeIter == actionLookup.end()) {
        actionType = ActKeyword::undefined;
    } else {
        actionType = actionTypeIter->second;
    }


    std::stringstream actionDescription;
    switch (actionType) {
    case ActKeyword::say: {
        actionDescription << u8"SayAction will be created";
        break;
    }
    case ActKeyword::look: {
        actionDescription << u8"LookAction will be created";
        break;
    }
    case ActKeyword::move: {
        actionDescription << u8"MoveAction will be created";
        break;
    }
    case ActKeyword::attack: {
        actionDescription << u8"AttackAction will be created";
        break;
    }
    default:
        actionDescription << u8"Action was not supported";
    }

    actionDescription << ", with remainder tokens [" << tokenRep.str() << "]";
    return actionDescription.str();
}

}  // namespace commandparser
}  // namespace mudserver