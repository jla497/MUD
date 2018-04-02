//
// Created by jla497 on 11/03/18.
//

#include "states/IState.h"
namespace state {
IState::IState(GameState *state, CharacterEntity *entity,
               CharacterController *controller)
    : state(state), entity(entity), controller(controller) {}
} // namespace state