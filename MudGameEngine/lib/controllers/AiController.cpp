//
// Created by jla497 on 11/03/18.
//
#include "controllers/AiController.h"
#include "states/IState.h"
#include "states/WaitState.h"
#include "states/InteractState.h"
using namespace state;
using namespace event;


void AiController::init(GameState *state, CharacterEntity *ent,
                        Player *plyer) {
    entity = ent;
    player = plyer;

    AiController::rules[StateType::wait] = {
            {EventType::interact, StateType::interact},
            {EventType::say, StateType::interact},
            {EventType::died_self, StateType::end}
    };

    AiController::rules[StateType::interact] = {
            {EventType::alone, StateType::wait},
            {EventType::startcombat, StateType::combat},
            {EventType::died_self, StateType::end}
    };

    AiController::rules[StateType::combat] = {
            {EventType::endcombat, StateType::interact},
            {EventType::alone, StateType::wait},
            {EventType::died_self, StateType::end}
    };

    stateDict[StateType::wait] = new state::WaitState(state, ent, this);
    stateDict[StateType::interact] = new state::InteractState(state, ent, this);
    stateDict[StateType::combat] = nullptr;
    stateDict[StateType::end] = nullptr;

    //set current to waitstate
    auto itr = stateDict.find(StateType::wait);
    currentState = itr->second;
}

void AiController::update() {
    std::cout<<"in controller..."<<std::endl;
    if(!eventQueue.empty()) {
        auto trigger = eventQueue.top();
        if(trigger.type != event::EventType::undefined) {
            auto triggerType = trigger.type;
            auto currentStateType = currentState->getType();
            auto events = rules[currentStateType];

            for(auto& pair : events) {
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

