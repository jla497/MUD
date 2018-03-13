//
// Created by jla497 on 11/03/18.
//

#include "controllers/CharacterController.h"
#include "states/IState.h"
#include "states/WaitState.h"

void CharacterController::init(GameState &state, CharacterEntity &entity) {
    stateDict["wait"] = new WaitState(state, entity, *this);
    auto itr = stateDict.find("wait");
    current = itr->second;
//    stateDict.add("interact", InteractState(state, entity, this));
}

void CharacterController::add(std::string key, IState *state) {
    stateDict[key] = state;
}

void CharacterController::remove(std::string id) {
    stateDict.erase(id);
}

void CharacterController::change(std::string id) {
    current->exit();
    auto itr = stateDict.find(id);
    if(itr != stateDict.end()) {
        current = itr->second;
    }
}
