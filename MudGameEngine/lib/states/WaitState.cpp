//
// Created by jla497 on 11/03/18.
//

#include "states/WaitState.h"


void WaitState::update() {
    auto room = state.getCharacterLocation(entity);
    auto chIds = state.getCharactersInRoom(room);
    for(auto id: chIds) {
        auto character = state.getCharacterFromLUT(id);
        if(character->get_isPlayerCharacter()) {
//            stateMachine.change("interact");
            std::cout<<"player's character entered the room. Switching to interactState..."<<std::endl;
        }
    }
}
void WaitState::enter() {};
void WaitState::exit() {};