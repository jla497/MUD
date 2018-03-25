//
// Created by jla497 on 25/03/18.
//

#ifndef ADVENTURE2018_ENDSTATE_H
#define ADVENTURE2018_ENDSTATE_H
#include "IState.h"
#include "Event.h"

namespace state{
    class EndState : public IState {
    public:
        using IState::IState;
        void update() override;
        void enter() override;
        void exit() override;
        StateType getType() override;
    };
}
#endif //ADVENTURE2018_ENDSTATE_H
