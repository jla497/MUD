//
// Created by jla497 on 11/03/18.
//

#include "controllers/CharacterController.h"
#include "states/IState.h"
#include "states/WaitState.h"
#include "gamemanager/GameState.h"

void CharacterController::init(GameState &state, CharacterEntity *ent, Player *plyer) {
    entity = ent;
    player = plyer;
    stateDict["wait"] = new WaitState(state, *ent, *this);
    auto itr = stateDict.find("wait");
    current = itr->second;
//    stateDict.add("interact", InteractState(state, entity, this));
    std::cout<<"finished initializing controller..."<<std::endl;
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

void CharacterController::setPlayer(Player* plyer){
    player = plyer;
}
Player* CharacterController::getPlayer(){
    return player;
}

void CharacterController::setCharacter(CharacterEntity* ent){
    entity = ent;
}
CharacterEntity* CharacterController::getCharacter() {
    return entity;
}

void CharacterController::setCmdString(std::string cmd) {
    cmdString = cmd;
}
std::string CharacterController::getCmdString() {
    return cmdString;
}

