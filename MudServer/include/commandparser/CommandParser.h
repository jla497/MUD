#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <experimental/string_view>
#include <string>
#include <unordered_map>

#include "actions/Action.h"
#include "entities/CharacterEntity.h"

#include "actions/Action.h"
#include "entities/PlayerCharacter.h"

class Action; // forward declaration

namespace mudserver {
namespace gamemanager {
class GameManager; // forward declaration
}

namespace commandparser {

using StrView = std::experimental::string_view;

enum class ActKeyword {
    undefined = 0,
    say,
    look,
    move,
    attack,

    _N_ACTIONS_
};

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
    actionFromPlayerCommand(PlayerCharacter &character, StrView command,
                            gamemanager::GameManager &gameManager);
};

} // namespace commandparser
} // namespace mudserver

#endif // COMMANDPARSER_H
