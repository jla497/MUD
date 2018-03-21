//
// Created by jla497 on 11/03/18.
//
#include "controllers/AiController.h"
#include "states/IState.h"
#include "states/WaitState.h"
#include "states/InteractState.h"

void AiController::init(GameState *state, CharacterEntity *ent,
                        Player *plyer) {
    entity = ent;
    player = plyer;
    stateDict["wait"] = new WaitState(state, ent, this);
    stateDict["interact"] = new InteractState(state, ent, this);

    //set current to waitstate
    auto itr = stateDict.find("wait");
    current = itr->second;
}

void AiController::update() {
    current->update();
}
