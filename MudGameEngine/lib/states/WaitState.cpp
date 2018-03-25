//
// Created by jla497 on 11/03/18.
//

#include "states/WaitState.h"
#include "Event.h"

namespace state {

    void WaitState::update() {
        std::cout<<"in waitstate..."<<std::endl;
        auto e = controller->getEvent();
        std::cout<<"13"<<std::endl;
        if(e.type != event::EventType::undefined) {

        }else {
            auto room = state->getCharacterLocation(*entity);
            auto chIds = state->getCharactersInRoom(room);
            for (auto id : chIds) {
                auto character = state->getCharacterFromLUT(id);
                if (character->get_isPlayerCharacter()) {
                    controller->setCmdString("say hello");
                    auto e = event::Event{};
                    e.entity = character;
                    e.type = event::EventType::interact;
                    e.args = {"foo","bar"};
                    controller->passEvent(e);
                }
            }
        }

    }
    void WaitState::enter(){};
    void WaitState::exit(){};

    StateType WaitState::getType() {
        return StateType::wait;
    }
}