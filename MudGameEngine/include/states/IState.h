//
// Created by jla497 on 11/03/18.
//

#ifndef ADVENTURE2018_ISTATE_H
#define ADVENTURE2018_ISTATE_H

#include "controllers/CharacterController.h"
#include "entities/CharacterEntity.h"
#include "gamemanager/GameState.h"

namespace mudserver {
namespace gamemanager {
class GameState;
}
} // namespace mudserver

using mudserver::gamemanager::GameState;

class IState {

  public:
    IState(GameState *state, CharacterEntity *entity,
           CharacterController *controller);
    virtual void update() = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;

  protected:
    GameState *state;
    CharacterEntity *entity;
    CharacterController *controller;
};
#endif // ADVENTURE2018_ISTATE_H
