//
// Created by jla497 on 25/03/18.
//

#ifndef ADVENTURE2018_COMBATSTATE_H
#define ADVENTURE2018_COMBATSTATE_H
#include "Event.h"
#include "IState.h"

namespace state {
class CombatState : public IState {
    CharacterEntity *targetEntity;

  public:
    using IState::IState;
    void update() override;
    void enter() override;
    void exit() override;
    StateType getType() override;
};
} // namespace state
#endif // ADVENTURE2018_COMBATSTATE_H
