//
// Created by jla497 on 13/03/18.
//

#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

#include "states/Dialogue.h"
#include "states/InteractState.h"

namespace state {

using Tokenizer = boost::tokenizer<boost::char_separator<char>>;

void InteractState::update() {
    auto dialogue = Dialogue();
    auto e = controller->getEvent();
    //        std::cout << "in interactstate..." << std::endl;

    switch (e.getType()) {

    case event::EventType::interact: {
        auto newEntity = e.getEntity();
        auto greeting = "say Hello " + newEntity->getShortDesc();
        controller->setCmdString(greeting);
        break;
    }

    case event::EventType::say: {
        auto tokens = e.getArgs();
        for (auto &token : tokens) {
            auto response = dialogue.getResponse(token);
            if (!response.empty()) {
                controller->setCmdString(response);
            }
        }
        break;
    }

    case event::EventType::undefined: {
        auto room = state->getCharacterLocation(*entity);
        auto chIds = state->getCharactersInRoom(room);
        for (auto id : chIds) {
            auto character = state->getCharacterFromLUT(id);
            if (character->get_isPlayerCharacter()) {
                return;
            }
        }

        auto e = event::Event{nullptr, event::EventType::alone, {}};
        controller->passEvent(e);
    }
    default:
        std::cout << "not a valid option" << std::endl;
        // do nothing
    }
    return;
}
void InteractState::enter(){};
void InteractState::exit(){};
StateType InteractState::getType() { return StateType::interact; }
}