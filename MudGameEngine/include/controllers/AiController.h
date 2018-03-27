//
// Created by jla497 on 11/03/18.
//

#ifndef ADVENTURE2018_AICONTROLLER_H
#define ADVENTURE2018_AICONTROLLER_H

#include <map>
#include <queue>

#include "Event.h"
#include "controllers/CharacterController.h"
#include "states/IState.h"

class AiController : public CharacterController {
  private:
    std::map<state::StateType, state::IState *> stateDict{};
    state::IState *currentState = nullptr;
    std::map<state::StateType,
             std::vector<std::pair<event::EventType, state::StateType>>>
        rules;

  public:
    using CharacterController::CharacterController;
    void init(GameState *state, CharacterEntity *ent, Player *plyer);
    void update() override;
};

#endif // ADVENTURE2018_AICONTROLLER_H
