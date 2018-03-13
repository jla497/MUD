
#pragma once

#include <string>

/*
 * To add a string:
 *   - add a value to StrKey
 *   - map it in keyStrMap in i18n.cpp
 *   - actually put it in a yml file somewhere
 *
 * To add a language:
 *   - add a value to LangKey
 *   - map it in langFileMap in i18n::init in i18n.cpp
 *   - actually write a yml file for it
 */

enum class StrKey : int {
    // put a space between groups
    ACTION_UNDEFINED,
    ACTION_SAY,
    ACTION_LOOK,
    ACTION_ATTACK,
    ACTION_MOVE,
    ACTION_PROGRAM,
    ACTION_TIMED,
    ACTION_SAVE,
    ACTION_CHARMOD,
    ACTION_HALT,
    ACTION_SWAP,

    _N_STRINGS_
};

enum class LangKey : int {
    EN_US,

    _TESTING_SMURF_,
    _N_LANGS_,
    _USE_APPROPRIATE_, // use whichever one is deemed to be appropriate
    // assigned keys must go last
    _DEFAULT_LANG_ = EN_US
};

namespace i18n {
constexpr const char *DEFAULT_STRING = "<MISSING_STRING>";

void init();
std::string get(StrKey str, LangKey lang = LangKey::_USE_APPROPRIATE_);
} // namespace i18n
