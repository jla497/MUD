//
// Created by jla497 on 25/03/18.
//

#ifndef ADVENTURE2018_ACTIONOBSERVER_H
#define ADVENTURE2018_ACTIONOBSERVER_H

#include "observe/Observer.h"

class Action;
class AttackAction;
class MoveAction;
class SayAction;
class CharacterController;
class CharacterEntity;
namespace mudserver {
namespace gamemanager {
class GameState;
}
}

using mudserver::gamemanager::GameState;

class ActionObserver : public Observer<Action> {
    // init map of characterentity to charactercontroller
    std::map<CharacterEntity *, CharacterController *> characterToControllers;
    GameState *gameState;
    std::vector<CharacterEntity *> CharactersInRoom(Action *action);

  public:
    ActionObserver(std::vector<CharacterController *> *controllers,
                   GameState *gameState);
    void receiveEvent(Action *source) override;
    void visit(AttackAction *action);
    void visit(MoveAction *action);
    void visit(SayAction *action);
};
#endif // ADVENTURE2018_ACTIONOBSERVER_H
