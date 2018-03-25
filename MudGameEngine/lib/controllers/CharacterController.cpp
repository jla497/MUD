//
// Created by jla497 on 11/03/18.
//

#include <queue>
#include "controllers/CharacterController.h"
#include "gamemanager/GameState.h"
#include "states/IState.h"

void CharacterController::init(GameState *s, CharacterEntity *e,
                               Player *p) {
    entity = e;
    player = p;
    state = s;
}

void CharacterController::setPlayer(Player *plyer) { player = plyer; }
Player *CharacterController::getPlayer() { return player; }

void CharacterController::setCharacter(CharacterEntity *ent) { entity = ent; }
CharacterEntity *CharacterController::getCharacter() { return entity; }

void CharacterController::setCmdString(std::string cmd) {
    cmdStrings.push(cmd);
}

std::string CharacterController::getCmdString() {
    if(cmdStrings.empty()) {
        return "";
    }
    auto res = cmdStrings.front();
    cmdStrings.pop();
    return res;
}

void CharacterController::passEvent(event::Event e) {
    eventQueue.push(e);
}

event::Event CharacterController::getEvent() {
    if(eventQueue.empty()){
        return event::Event{};
    }
    auto e = eventQueue.top();
    eventQueue.pop();
    return e;
}
