//
// Created by jla497 on 11/03/18.
//

#ifndef ADVENTURE2018_CHARACTERCONTROLLER_H
#define ADVENTURE2018_CHARACTERCONTROLLER_H

#include "Event.h"
#include "entities/CharacterEntity.h"
#include "entities/CharacterEntity.h"
#include "gamemanager/Player.h"
#include <queue>
#include <unordered_map>

namespace state {
enum class StateType;
class IState;
}

namespace mudserver {
namespace gamemanager {
class GameState;
}
}

using mudserver::gamemanager::GameState;
using mudserver::gamemanager::Player;

class CharacterController {

  protected:
    GameState *state = nullptr;
    Player *player = nullptr;
    CharacterEntity *entity = nullptr;
    std::queue<std::string> cmdStrings;
    std::priority_queue<event::Event> eventQueue;

  public:
    void init(GameState *state, CharacterEntity *entity, Player *plyer);
    virtual void update() = 0;
    void passEvent(event::Event e);
    event::Event getEvent();
    void setPlayer(Player *player);
    Player *getPlayer();
    void setCharacter(CharacterEntity *entity);
    CharacterEntity *getCharacter();
    void setCmdString(std::string cmd);
    std::string getCmdString();
};
#endif // ADVENTURE2018_CHARACTERCONTROLLER_H
