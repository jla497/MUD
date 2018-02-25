#include "actions/PrgmAction.h"
#include <regex>

using boost::algorithm::to_lower;
using boost::algorithm::erase_all;
using namespace mudserver::resources::commands;
using namespace mudserver::resources::playercharacter;

std::unordered_map<std::string, PrgmAction::PrgmKeyword> PrgmAction::prgmLookup = {
        {NPC, PrgmAction::PrgmKeyword::npc},
        {PC, PrgmAction::PrgmKeyword::pc},
        {OBJECT, PrgmAction::PrgmKeyword::object}
};

PrgmAction::PrgmParser::OptValMap PrgmAction::PrgmParser::optionLookup = {
        {CREATE, "--create <other options...>"},
        {MODIFY, "--modify <id>"},
        {CSHORTDESC, "--shortdesc <string>"},
        {CARMOR, "--armor <int>"},
        {CDAMAGE, "--damage <string>"},
        {CEXP, "--experience <int>"},
        {CGOLD, "--gold <int>"},
        {CLEVEL, "--level <int>"}
};


void PrgmAction::execute_impl() {
    static auto logger =
        mudserver::logging::getLogger("ProgramAction::execute");

    std::string userinfo(
            "userid: " +
            std::to_string(characterPerformingAction.getEntityId().getId()));
    logger->info(userinfo);

    if (actionArguments.empty()) {
        logger->error("Not a valid Program command...");
        gameManager.sendCharacterMessage(
                characterPerformingAction.getEntityId(),
                "Not a valid Program command...");
        return;
    }

    auto cmd = actionArguments[0];
    to_lower(cmd);
    auto actionTypeIter = prgmLookup.find(cmd);

    auto actionType = (actionTypeIter == prgmLookup.end())
                            ? PrgmKeyword::undefined
                            : actionTypeIter->second;


    // get first arg: Possible options: {npc, character, object ...}
    switch(actionType) {
        case PrgmKeyword::npc: {
            prgmNpc();
            break;
        }
        case PrgmKeyword::pc: {
            createPc();
            break;
        }
        case PrgmKeyword::object: {
            prgmObject();
            break;
        }
        default:
            logger->debug("not a valid program command");
    }
    //switch statements
}

void PrgmAction::prgmNpc() {
    static auto logger =
            mudserver::logging::getLogger("ProgramAction::execute");
    auto characterID = characterPerformingAction.getEntityId();
    PrgmAction::PrgmParser parser {};
    try{
        auto map = parser.parseOptValPairs(actionArguments);
        if(map.find(HELP) != map.end()) {
            gameManager.sendCharacterMessage(
                    characterID,
                    map["help"]);
            return;
        }

        if(map.find(MODIFY) != map.end()) {

            auto &state = gameManager.getState();
            auto id = stoi(map.find(MODIFY)->second);
            auto character = state.getCharacterFromLUT(UniqueId {id});
            if(character == nullptr) {
                logger->debug("character is null");
                return;
            }
            auto &factory = state.getFactory();
            factory.modifyCharacter(character, map);

        }

        //check in lut if it's valid option
        //if it's valid option convert  to correct datatype
        //pass params to entityfactory to build new npc and replace old one

    }catch(std::string e){
        gameManager.sendCharacterMessage(
                characterID,
                e);
    }

}


void PrgmAction::prgmPc() {

}

void PrgmAction::createPc() {
    static auto logger =
            mudserver::logging::getLogger("ProgramAction::execute");

    auto spawnLocationId =std::stoi(actionArguments[1]);
    auto &state = gameManager.getState();
    auto newPc = std::make_unique<PlayerCharacter>(
            ARMOR, std::string{DAMAGE}, std::vector<std::string>{}, EXP,
            GOLD, std::string{HIT}, std::vector<std::string>{}, LEVEL,
            std::vector<std::string>{}, "new character added by admin", THAC0);

    auto newPcPtr = newPc.get();
    state.addCharacter(std::move(newPc));
    state.addCharacterRoomRelationToLUT(newPcPtr->getEntityId(),spawnLocationId);

}


void PrgmAction::prgmObject() {
    static auto logger =
            mudserver::logging::getLogger("ProgramAction::execute");

    logger->debug("prgmObject executed");
}


PrgmAction::PrgmParser::OptValMap PrgmAction::PrgmParser::parseOptValPairs(std::vector<std::string> actionArguments) {
    std::unordered_map<std::string, std::string> optionMap;
    std::regex regExOptions("(\\-\\-[a-z]+)");
    std::regex removeNL("\t|\n|\r");
    std::regex validInput("[a-zA-Z0-9]+");

    for(size_t i =0; i < actionArguments.size(); i++) {
        auto opt = actionArguments[i];
        opt = std::regex_replace(opt, removeNL, "");

        if (std::regex_match(opt,regExOptions)) {

            std::string input;
            if(opt == HELP) {
                input = this->printHelp();
                optionMap[opt]=input;
                return optionMap;
            } else {
                input = actionArguments[++i];
            }

            input = std::regex_replace(input, removeNL, "");
            if(std::regex_match(input, validInput)) {optionMap[opt] = input;}
        }
    }
    optionValuePairs = optionMap;
    return optionMap;
};


std::string PrgmAction::PrgmParser::getArgument(std::string arg){
    auto itr = optionValuePairs.find(arg);
    if(itr == optionValuePairs.end()) {
        throw "invalid arg";
    }
    return itr->second;
}
