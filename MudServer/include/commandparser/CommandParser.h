#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <experimental/string_view>
#include <string>
#include <unordered_map>

#include "actions/Action.h"
#include "controllers/CharacterController.h"
#include "entities/CharacterEntity.h"
#include "gamemanager/Player.h"

class Action; // forward declaration

namespace mudserver {
namespace gamemanager {
class GameManager; // forward declaration
}

namespace commandparser {

using gamemanager::PasswordType;
using gamemanager::Player;
using gamemanager::UsernameType;
using StrView = std::experimental::string_view;

enum class AliasReturnCode { SUCCESS, INVALID_KEYWORD, ALIAS_EXISTS };

AliasReturnCode registerCommandAlias(ActKeyword keyword,
                                     const std::string &alias);

/**
 * Uses Factory pattern to create correct derived type of Action depending on
 * input.
 */
class CommandParser {
  public:
    CommandParser() = default;

    /**
     * Creates an Action from a player's command string. Called by GameManager
     * when handling input from server.
     *
     * @param character reference to the player's character who is performing
     *                  the action
     * @param command a string containing the command ex. "attack shopkeeper"
     * @param gameManager reference to the game manager so that actions can
     *                    queue messages or alter game state
     * @return the generated Action (will be a derived class)
     */
    std::unique_ptr<Action>
    actionFromPlayerCommand(CharacterController &controller, StrView command,
                            gamemanager::GameManager &gameManager);
    std::pair<UsernameType, PasswordType>
    identifiersFromIdentifyCommand(StrView command);
};

} // namespace commandparser
} // namespace mudserver

#endif // COMMANDPARSER_H
