//
// Created by jla497 on 11/03/18.
//

#include <queue>
#include "controllers/CharacterController.h"
#include "gamemanager/GameState.h"
#include "states/IState.h"

void CharacterController::init(GameState *state, CharacterEntity *ent,
                               Player *plyer) {
    entity = ent;
    player = plyer;

}

void CharacterController::add(std::string key, IState *state) {
    stateDict[key] = state;
}

void CharacterController::remove(std::string id) { stateDict.erase(id); }

void CharacterController::change(std::string id) {
    current->exit();
    auto itr = stateDict.find(id);
    if (itr != stateDict.end()) {
        current = itr->second;
        std::cout<<"switched state to "+id<<std::endl;
    }
}

void CharacterController::setPlayer(Player *plyer) { player = plyer; }
Player *CharacterController::getPlayer() { return player; }

void CharacterController::setCharacter(CharacterEntity *ent) { entity = ent; }
CharacterEntity *CharacterController::getCharacter() { return entity; }

void CharacterController::setCmdString(std::string cmd) {
    cmdStrings.push(cmd);
}

std::string CharacterController::getCmdString() {
    auto res = cmdStrings.front();
    cmdStrings.pop();
    return res;
}


void CharacterController::setMsg(std::string msg) {
    messages.push(msg);
}

std::string CharacterController::getMsg() {
    auto res = messages.front();
    messages.pop();
    return res;
}

std::queue<std::string> CharacterController::getAllMsgs() {
    auto res = messages;
    std::queue<std::string> empty;
    messages.swap(empty);
    return res;
}