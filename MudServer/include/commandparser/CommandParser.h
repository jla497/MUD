#ifndef ADVENTURE2018_COMMANDPARSER_H
#define ADVENTURE2018_COMMANDPARSER_H

#include <experimental/string_view>
#include <unordered_map>
#include <string>

#include "gamemanager/Character.h"

namespace mudserver {
namespace commandparser {

using StrView = std::experimental::string_view;

enum class ActKeyword {
    undefined,
    say,
    look,
    move,
    attack,
    actions
};

class CommandParser {
    static std::unordered_map<std::string, ActKeyword> actionLookup;
public:
    CommandParser();
    std::string actionFromPlayerCommand(gamemanager::Character* character,
                                        StrView command);
};

}  // namespace commandparser
}  // namespace mudserver

#endif  // ADVENTURE2018_COMMANDPARSER_H
