//
// Created by jla497 on 11/03/18.
//

#ifndef ADVENTURE2018_INTERACTSTATE_H
#define ADVENTURE2018_INTERACTSTATE_H

#include "IState.h"

class InteractState : public IState {
  public:
    using IState::IState;
    void update() override;
    void enter() override;
    void exit() override;
};
#endif // ADVENTURE2018_INTERACTSTATE_H
