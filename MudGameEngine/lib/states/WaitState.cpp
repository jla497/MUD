//
// Created by jla497 on 11/03/18.
//

#include "states/WaitState.h"
#include "Event.h"

namespace state {

    void WaitState::update() {
        auto e = controller->getEvent();
        if(e.getType() != event::EventType::undefined) {

        }else {
            auto room = state->getCharacterLocation(*entity);
            auto chIds = state->getCharactersInRoom(room);
            for (auto id : chIds) {
                auto character = state->getCharacterFromLUT(id);
                if (character->get_isPlayerCharacter()) {
                    auto e = event::Event{character,
                                          event::EventType::interact,
                                          {"foo"}
                                         };
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