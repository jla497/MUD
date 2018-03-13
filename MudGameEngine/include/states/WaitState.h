//
// Created by jla497 on 11/03/18.
//

#ifndef ADVENTURE2018_WAITSTATE_H
#define ADVENTURE2018_WAITSTATE_H

#include "states/IState.h"

class WaitState : public IState {

public:
    using IState::IState;
    void update() override;
    void enter() override;
    void exit() override;
};
#endif //ADVENTURE2018_WAITSTATE_H
