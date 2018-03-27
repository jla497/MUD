//
// Created by jla497 on 11/03/18.
//
#include "controllers/AiController.h"
#include "states/CombatState.h"
#include "states/EndState.h"
#include "states/IState.h"
#include "states/InteractState.h"
#include "states/WaitState.h"

using state::StateType;
using event::EventType;

void AiController::init(GameState *state, CharacterEntity *ent, Player *plyer) {

    entity = ent;
    player = plyer;

    AiController::rules[StateType::wait] = {
        {EventType::interact, StateType::interact},
        {EventType::say, StateType::interact},
        {EventType::died_self, StateType::end}};

    AiController::rules[StateType::interact] = {
        {EventType::alone, StateType::wait},
        {EventType::startcombat, StateType::combat},
        {EventType::died_self, StateType::end}};

    AiController::rules[StateType::combat] = {
        {EventType::endcombat, StateType::interact},
        {EventType::died_self, StateType::end}};

    stateDict[StateType::wait] = new state::WaitState(state, ent, this);
    stateDict[StateType::interact] = new state::InteractState(state, ent, this);
    stateDict[StateType::combat] = new state::CombatState(state, ent, this);
    stateDict[StateType::end] = new state::EndState(state, ent, this);

    // set current to waitstate
    auto itr = stateDict.find(StateType::wait);
    currentState = itr->second;
}

void AiController::update() {
    if (!eventQueue.empty()) {
        auto trigger = eventQueue.top();
        if (trigger.getType() != event::EventType::undefined) {
            auto triggerType = trigger.getType();
            auto currentStateType = currentState->getType();
            auto events = rules[currentStateType];

            for (auto &pair : events) {
                auto thisTrigger = pair.first;
                if (thisTrigger == triggerType) {
                    auto nextStateType = pair.second;
                    currentState = stateDict[nextStateType];
                }
            }
        }
    }
    currentState->update();
}
