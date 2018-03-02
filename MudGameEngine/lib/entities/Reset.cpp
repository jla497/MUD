#include "reset/Reset.h"
#include "gamemanager/GameState.h"
#include <boost/algorithm/string.hpp>
#include <string>
#include <utility>
#include <vector>

std::unordered_map<std::string, Reset::ResetKeyword> Reset::resetLookUp = {
    {"object", Reset::ResetKeyword::object},
    {"npc", Reset::ResetKeyword::npc},
    {"door", Reset::ResetKeyword::door},
    {"equip", Reset::ResetKeyword::equip}};

Reset::Reset(int id, std::string action, std::string comment, std::string state,
             int slot, int limit, int roomID)
    : id{id}, action{action}, comment{comment}, state{state}, slot{slot},
      limit{limit}, roomID{roomID} {}

void Reset::resetNpc(mudserver::gamemanager::GameState &state) {
    static auto logger =
        mudserver::logging::getLogger("Reset::execute::resetNPC");
    auto &factory = state.getFactory();
    auto npc = factory.buildNpc(id);
    try {
        state.addCharacter(npc, roomID);
    } catch (std::exception e){
        logger->debug(e.what());
    }
}

void Reset::execute(mudserver::gamemanager::GameState &state) {
    static auto logger = mudserver::logging::getLogger("Reset::execute");
    auto resetTypeIter =
        resetLookUp.find(boost::algorithm::to_lower_copy(action));
    auto resetT = (resetTypeIter == resetLookUp.end())
                      ? Reset::ResetKeyword::undefined
                      : resetTypeIter->second;

    switch (resetT) {
    case Reset::ResetKeyword::npc: {
        logger->info("npc reset");
        resetNpc(state);
        break;
    }

    case Reset::ResetKeyword::object: {
        //        logger->info("object reset");
        break;
    }

    case Reset::ResetKeyword::door: {
        //        logger->info("door reset");
        break;
    }

    case Reset::ResetKeyword::equip: {
        //        logger->info("equip reset");
        break;
    }
    default:
        logger->info("not a valid reset code");
    }
}
