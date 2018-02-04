#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <experimental/string_view>
#include <unordered_map>
#include <string>

#include "gamemanager/GameManager.h"
#include "gamemanager/Character.h"
#include "actions/Action.h"

namespace mudserver {
namespace gamemanager { class GameManager; }      // fix for circular dependency

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
    CommandParser() = default;
    std::unique_ptr<Action> actionFromPlayerCommand(
        gamemanager::Character* character, StrView command,
        gamemanager::GameManager& gameManager);
};

}  // namespace commandparser
}  // namespace mudserver

#endif  // COMMANDPARSER_H
