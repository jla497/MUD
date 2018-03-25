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
        if(e.getType() != event::EventType::undefined) {
            auto newEntity = e.getEntity();
            std::cout<<"in interactstate..."<<std::endl;
            srand(time(0));
            int randomval = rand() % 2;
            if(randomval > 0) {
                auto greeting = "say Hello "+newEntity->getShortDesc();
                controller->setCmdString(greeting);
                return;
            }else{
                auto e = event::Event{
                        newEntity,
                        event::EventType::startcombat,
                        {}
                };
                controller->passEvent(e);
                return;
            }

        }else {
            //check if anyone is still in room, if not pass alone event
            auto room = state->getCharacterLocation(*entity);
            auto chIds = state->getCharactersInRoom(room);
            for (auto id : chIds) {
                auto character = state->getCharacterFromLUT(id);
                if (character->get_isPlayerCharacter()) {
                    return;
                }
            }

            auto e = event::Event{ nullptr,
                                   event::EventType::alone,
                                   {}
                                 };
        controller->passEvent(e);
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

        return;
    }
    void InteractState::enter(){};
    void InteractState::exit(){};
    StateType InteractState::getType() {
        return StateType::interact;
    }
}