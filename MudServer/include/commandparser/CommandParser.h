#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <experimental/string_view>
#include <unordered_map>
#include <string>

#include "gamemanager/Character.h"
#include "actions/Action.h"
#include "entities/CharacterEntity.h"


class Action;                                     // forward declaration
namespace mudserver {
namespace gamemanager { class GameManager; }      // forward declaration

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
       CharacterEntity* character, StrView command,
        gamemanager::GameManager& gameManager);
};

}  // namespace commandparser
}  // namespace mudserver

#endif  // COMMANDPARSER_H
