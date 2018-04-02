#include <cassert>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "i18n/i18n.h"
#include "logging.h"

using StrKeyMap = std::unordered_map<StrKey, std::string>;
static std::unordered_map<LangKey, StrKeyMap> langMap;

#define map(key)                                                               \
    { #key, StrKey::key }

static std::unordered_map<std::string, StrKey> keyStrMap = { // NOLINT
    map(ACTION_UNDEFINED), map(ACTION_SAY),  map(ACTION_LOOK),
    map(ACTION_ATTACK),    map(ACTION_MOVE), map(ACTION_PROGRAM),
    map(ACTION_TIMED),     map(ACTION_SAVE), map(ACTION_CHARMOD),
    map(ACTION_HALT),      map(ACTION_SWAP), map(ACTION_CAST)};

#undef map

template <typename T, typename = std::enable_if<std::is_enum<T>::value>>
std::string to_string(T value) noexcept {
    return std::to_string(
        static_cast<typename std::underlying_type<T>::type>(value));
}

static StrKeyMap loadFromFile(const std::string &file) {
    StrKeyMap map;
    auto logger = mudserver::logging::getLogger("i18n::loadFromFile");
    auto root = YAML::LoadFile(file)["strings"];
    for (const auto &pair : keyStrMap) {
        const auto &node = root[pair.first];
        if (node.IsDefined()) {
            map.emplace(pair.second, node.as<std::string>());
        } else {
            logger->warning("Missing string " + to_string(pair.second) +
                            " in " + file + "\n");
        }
    }
    return map;
}

static LangKey APPROPRIATE_LANG = LangKey::_DEFAULT_LANG_;

void i18n::init() {
    const static std::vector<std::pair<LangKey, std::string>> langFileMap = {
        {LangKey::EN_US, "locales/en-us.yml"},
        {LangKey::_TESTING_SMURF_, "locales/smurflang.yml"}};
    /*
     * Allow init to be called multiple times, but only allow it to happen once.
     * Multiple things want access to i18n, so multiple things depend on init
     * being called. If they can call it themselves, there's no worry.
     */
    static bool done = false;
    if (!done) {
        done = true;
        for (const auto &pair : langFileMap) {
            langMap.emplace(pair.first, loadFromFile(pair.second));
        }
        // TODO modify APPROPRIATE_LANG based on current locale
    }
}

std::string i18n::get(StrKey str, LangKey lang) {
    if (lang == LangKey::_USE_APPROPRIATE_) {
        lang = APPROPRIATE_LANG;
        assert(lang != LangKey::_USE_APPROPRIATE_);
    }
    const auto lit = langMap.find(lang);
    if (lit != langMap.end()) {
        const auto &strMap = lit->second;
        const auto sit = strMap.find(str);
        if (sit != strMap.end()) {
            return sit->second;
        }
    }
    // the desired string doesn't exist for this locale
    auto logger = mudserver::logging::getLogger("i18n::get");
    if (lang == LangKey::_DEFAULT_LANG_) {
        logger->error("Missing string " + to_string(str) +
                      " for default lang\n");
        return DEFAULT_STRING;
    }
    logger->warning("Missing string " + to_string(str) + " for lang " +
                    to_string(lang) + "\n");
    return get(str, LangKey::_DEFAULT_LANG_);
}
