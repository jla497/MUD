//
// Created by jla497 on 11/03/18.
//

#include "states/WaitState.h"
#include "Event.h"

namespace state {

void WaitState::update() {
    // if a player in same room switch state
    controller->getEvent();
    auto room = state->getCharacterLocation(*entity);
    auto chIds = state->getCharactersInRoom(room);
    for (auto id : chIds) {
        auto character = state->getCharacterFromLUT(id);
        if (!(character->getEntityId() == entity->getEntityId())) {
            auto e =
                event::Event{character, event::EventType::interact, {"foo"}};
            controller->passEvent(e);
            return;
        }
    }

    // randomly move
    //    srand(time(NULL));
    //    auto chance = rand() % 5;
    //    if (chance > 3) {
    //        // find valid direction
    //        auto directions = room->getDirs();
    //        auto numOfDirs = directions.size();
    //        auto directionIndex = rand() % numOfDirs;
    //
    //        auto moveTo = directions[directionIndex];
    //        controller->setCmdString("move " + moveTo);
    //        std::cout << entity->getShortDesc() << " moved " << moveTo <<
    //        std::endl;
    //    }
}
void WaitState::enter(){};
void WaitState::exit(){};

StateType WaitState::getType() { return StateType::wait; }
} // namespace state