#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <iostream>
#include <sstream>
#include <memory>

#include "actions/AttackAction.h"
#include "actions/NullAction.h"
#include "actions/MoveAction.h"
#include "actions/SayAction.h"
#include "commandparser/CommandParser.h"
#include "resources/commands.h"
#include "logging.h"

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

std::unique_ptr<Action> CommandParser::actionFromPlayerCommand(
    gamemanager::Character* character, StrView command,
    gamemanager::GameManager& gameManager) {

    auto logger = logging::getLogger("CommandParser::actionFromPlayerCommand");

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

    std::stringstream actionDescription;
    std::unique_ptr<Action> action;
    std::ostringstream os;
    os<<character->getEntityId();
    // os << character->getId();
    auto idStr = os.str(); 
    switch (actionType) {
    case ActKeyword::say: {
        actionDescription << u8"SayAction will be created";
        action = std::make_unique<SayAction>(idStr, remainderOfTokens,
                                             gameManager);
        break;
    }

    case ActKeyword::move: {
        actionDescription << u8"MoveAction will be created";
        action = std::make_unique<MoveAction>(idStr, remainderOfTokens,
                                              gameManager);
        break;
    }
    case ActKeyword::attack: {
        actionDescription << u8"AttackAction will be created";
        action = std::make_unique<AttackAction>(idStr, remainderOfTokens,
                                                gameManager);
        break;
    }
    case ActKeyword::look: {
    }
    default:
        actionDescription << u8"Action was not supported";
        action = std::make_unique<NullAction>(idStr, remainderOfTokens,
                                              gameManager);
    }

    actionDescription << ", with remainder tokens [" << tokenRep.str() << "]";
    logger->debug(actionDescription.str());

    return action;
}

}  // namespace commandparser
}  // namespace mudserver