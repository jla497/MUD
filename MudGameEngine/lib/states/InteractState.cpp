//
// Created by jla497 on 13/03/18.
//

#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

#include "states/InteractState.h"
#include "states/Dialogue.h"

namespace state{

    using Tokenizer = boost::tokenizer<boost::char_separator<char>>;

//for each action
//if attack action. auto nameOfAttackTarget = boost::join(actionArguments, " ");
//get attacker

//if say action. auto see if recipient is you. find speaker


    void InteractState::update() {
        auto dialogue = Dialogue();
        auto e = controller->getEvent();
        if(e.type != event::EventType::undefined) {
            auto newEntity = e.entity;
            std::cout<<"in interactstate..."<<std::endl;
            if(e.args.empty()) {
                auto greeting = "say Hello "+newEntity->getShortDesc();
                controller->setCmdString(greeting);
                return;
            }else {
                //process args
            }
        }

//    auto msgs = controller->getAllMsgs();
//    auto mCharacter = controller->getCharacter();
//    auto mCharacterName = mCharacter->getShortDesc();
//    boost::algorithm::to_lower(mCharacterName);
//
//    while (!msgs.empty()) {
//        auto argString = msgs.front();
//        msgs.pop();
//
//        if(argString.empty()) {
//            continue;
//        }
//
//        std::vector<std::string> tokens;
//        //get sender's name
//        boost::split(tokens, argString, boost::is_any_of(" "));
//        auto recipient = tokens[1];
//        //message not for this NPC
//        if( recipient != mCharacterName) {
//            continue;
//        }
//
//        auto senderName = tokens[0];
//        boost::erase_all(senderName, ":");
//
//        for(auto & token : tokens) {
//            auto response = dialogue.getResponse(token);
//            if(!response.empty()) {
//                controller->setCmdString(response);
//            }
//        }
//    }
//
//    auto room = state->getCharacterLocation(*entity);
//    auto chIds = state->getCharactersInRoom(room);
//    for (auto id : chIds) {
//        auto character = state->getCharacterFromLUT(id);
//        if (character->get_isPlayerCharacter()) {
//            return;
//        }
//    }
//
//    controller->change("wait");
        return;
    }
    void InteractState::enter(){};
    void InteractState::exit(){};
    StateType InteractState::getType() {
        return StateType::interact;
    }
}