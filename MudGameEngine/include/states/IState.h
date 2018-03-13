//
// Created by jla497 on 11/03/18.
//

#ifndef ADVENTURE2018_ISTATE_H
#define ADVENTURE2018_ISTATE_H

#include "gamemanager/GameState.h"
#include "entities/CharacterEntity.h"
#include "controllers/CharacterController.h"

namespace mudserver{
    namespace gamemanager {
        class GameState;
    }
}

using mudserver::gamemanager::GameState;

class IState {

public:
    IState(GameState &state, CharacterEntity &entity, CharacterController &controller);
    virtual void update() = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;

protected:
    GameState &state;
    CharacterEntity &entity;
    CharacterController &controller;
};
#endif //ADVENTURE2018_ISTATE_H
