#include <exception>
#include <regex>

#include "actions/PrgmAction.h"

using boost::algorithm::to_lower;
using boost::algorithm::join;
using boost::algorithm::erase_all;

using namespace mudserver::resources::commands;
using namespace mudserver::resources::playercharacter;

std::unordered_map<std::string, PrgmAction::PrgmKeyword>
    PrgmAction::prgmLookup = {{NPC, PrgmAction::PrgmKeyword::npc},
                              {PC, PrgmAction::PrgmKeyword::pc},
                              {OBJECT, PrgmAction::PrgmKeyword::object}};

PrgmAction::PrgmParser::OptValMap PrgmAction::PrgmParser::optionLookup = {
    {CREATE, "--create <other options...>"},
    {MODIFY, "--modify <id>"},
    {CSHORTDESC, "--shortdesc <string>"},
    {CARMOR, "--armor <int>"},
    {CDAMAGE, "--damage <string>"},
    {CEXP, "--experience <int>"},
    {CGOLD, "--gold <int>"},
    {CLEVEL, "--level <int>"},
    {CHELP, "e.g. --modify/--create <id> --armor <int>"}};

PrgmAction *PrgmAction::clone() { return new PrgmAction(*this); }

void PrgmAction::execute_impl() {
    static auto logger =
        mudserver::logging::getLogger("ProgramAction::execute");

    //    std::string userinfo(
    //        "userid: " +
    //        std::to_string(characterPerformingAction.getEntityId().getId()));
    //    logger->info(userinfo);

    if (actionArguments.empty()) {
        logger->error("Not a valid Program command...");
        gameManager.sendCharacterMessage(
            characterPerformingAction.getEntityId(),
            "Not a valid Program command...");
        return;
    }

    //    auto cmd = actionArguments[0];
    //    to_lower(cmd);
    //    auto actionTypeIter = prgmLookup.find(cmd);
    //
    //    auto actionType = (actionTypeIter == prgmLookup.end())
    //                          ? PrgmKeyword::undefined
    //                          : actionTypeIter->second;
    //
    //    // get first arg: Possible options: {npc, character, object ...}
    //    switch (actionType) {
    //    case PrgmKeyword::npc: {
    //        prgmNpc();
    //        break;
    //    }
    //    case PrgmKeyword::pc: {
    //        createPc();
    //        break;
    //    }
    //    case PrgmKeyword::object: {
    //        prgmObject();
    //        break;
    //    }
    //    default:
    //        logger->debug("not a valid program command");
    //    }
    // switch statements
    prgmNpc();
}

void PrgmAction::prgmNpc() {
    static auto logger =
        mudserver::logging::getLogger("ProgramAction::execute");
    auto characterID = characterPerformingAction.getEntityId();
    PrgmAction::PrgmParser parser{};
    try {
        auto map = parser.parseOptValPairs(actionArguments);
        if (map.find(CHELP) != map.end()) {
            gameManager.sendCharacterMessage(characterID, map[CHELP]);
            return;
        }

        if (map.find(MODIFY) != map.end()) {

            auto &state = gameManager.getState();
            auto id = stoi(map.find(MODIFY)->second);
            auto character = state.getCharacterFromLUT(UniqueId{id});
            if (character == nullptr) {
                logger->debug("character is null");
                return;
            }
            auto &factory = state.getFactory();
            factory.modifyCharacter(character, map);
        }

    } catch (std::exception &e) {
        gameManager.sendCharacterMessage(characterID,
                                         "error parsing program options");
        logger->debug("error parsing program options");
    }
}

void PrgmAction::prgmObject() {
    static auto logger =
        mudserver::logging::getLogger("ProgramAction::execute");

    logger->debug("prgmObject executed");
}

PrgmAction::PrgmParser::OptValMap PrgmAction::PrgmParser::parseOptValPairs(
    std::vector<std::string> actionArguments) {

    std::unordered_map<std::string, std::string> optionMap{};
    std::regex regExOptions("([a-z]+)");
    std::regex removeNL("\t|\n|\r");
    std::regex validInput("[a-zA-Z0-9]+");

    for (auto it = actionArguments.begin(); it != actionArguments.end(); ++it) {
        auto opt = *it;

        if (std::regex_match(opt, regExOptions)) {
            std::string input{};
            if (opt == CHELP) {
                input = printHelp();
                optionMap[opt] = input;
                return optionMap;
            } else {
                it++;
                if (it != actionArguments.end()) {
                    input = *it;
                }
            }

            input = std::regex_replace(input, removeNL, "");
            if (std::regex_match(input, validInput)) {
                optionMap[opt] = input;
            }
        }
    }
    optionValuePairs = optionMap;
    return optionMap;
};

std::string PrgmAction::PrgmParser::getArgument(std::string arg) {
    auto itr = optionValuePairs.find(arg);
    if (itr == optionValuePairs.end()) {
        throw "invalid arg";
    }

    return itr->second;
}

std::string PrgmAction::PrgmParser::printHelp() {
    std::stringstream ss;
    for (const auto &pair : optionLookup) {
        ss << "option: " << pair.first << " info: " << pair.second << "\n";
    }
    return ss.str();
};
