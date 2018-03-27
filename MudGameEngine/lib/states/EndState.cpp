//
// Created by jla497 on 25/03/18.
//

//
// Created by jla497 on 11/03/18.
//

#include "states/EndState.h"
#include "Event.h"

namespace state {

void EndState::update() {}
void EndState::enter(){};
void EndState::exit(){};

StateType EndState::getType() { return StateType::wait; }
}