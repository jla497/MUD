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
#include "i18n/i18n.h"
#include "resources/commands.h"

namespace mudserver {
    namespace commandparser {

        using Tokenizer = boost::tokenizer<boost::char_separator<char>>;
        using boost::algorithm::to_lower_copy;

        using namespace resources::commands;

        static auto actionLookup =
                ([]() -> std::unordered_map<std::string, ActKeyword> { // NOLINT
                    i18n::init();
                    std::unordered_map<std::string, ActKeyword> ret = {
                            {i18n::get(StrKey::ACTION_UNDEFINED), ActKeyword::undefined},
                            {i18n::get(StrKey::ACTION_SAY), ActKeyword::say},
                            {i18n::get(StrKey::ACTION_LOOK), ActKeyword::look},
                            {i18n::get(StrKey::ACTION_ATTACK), ActKeyword::attack},
                            {i18n::get(StrKey::ACTION_MOVE), ActKeyword::move},
                            {i18n::get(StrKey::ACTION_PROGRAM), ActKeyword::program},
                            {i18n::get(StrKey::ACTION_TIMED), ActKeyword::timed},
                            {i18n::get(StrKey::ACTION_SAVE), ActKeyword::save},
                            {i18n::get(StrKey::ACTION_CHARMOD), ActKeyword::charmod},
                            {i18n::get(StrKey::ACTION_HALT), ActKeyword::halt},
                            {i18n::get(StrKey::ACTION_SWAP), ActKeyword::swap},
                            {i18n::get(StrKey::ACTION_CAST), ActKeyword::cast},
                            {i18n::get(StrKey::ACTION_TAKE), ActKeyword::take}};
                    return ret;
                })();

        template <typename T, typename = std::enable_if<std::is_enum<T>::value>>
        bool operator>=(T a, T b) {
            using U = typename std::underlying_type<T>::type;
            return static_cast<U>(a) >= static_cast<U>(b);
        }

        AliasReturnCode registerCommandalias(ActKeyword keyword,
                                             const std::string &alias) {
            if (keyword >= ActKeyword::_N_ACTIONS_) {
                return AliasReturnCode::INVALID_KEYWORD;
            }
            auto it = actionLookup.find(alias);
            if (it != actionLookup.end()) {
                return AliasReturnCode::ALIAS_EXISTS;
            }
            actionLookup.emplace(alias, keyword);
            return AliasReturnCode::SUCCESS;
        }

        std::unique_ptr<Action>
        CommandParser::actionFromPlayerCommand(CharacterController &controller,
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

            return Action::base(actionType)
                    ->clone(controller, remainderOfTokens, gameManager);
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
