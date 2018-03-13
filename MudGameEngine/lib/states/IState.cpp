//
// Created by jla497 on 11/03/18.
//

#include "states/IState.h"

IState::IState(GameState &state, CharacterEntity &entity, CharacterController &controller):
        state(state), entity(entity), controller(controller) {}
