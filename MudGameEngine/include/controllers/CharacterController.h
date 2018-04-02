//
// Created by jla497 on 11/03/18.
//

#ifndef ADVENTURE2018_CHARACTERCONTROLLER_H
#define ADVENTURE2018_CHARACTERCONTROLLER_H

#include "entities/CharacterEntity.h"
#include "gamemanager/Player.h"
#include <queue>
#include <unordered_map>

class IState;
namespace mudserver {
namespace gamemanager {
class GameState;
}
} // namespace mudserver

using mudserver::gamemanager::GameState;
using mudserver::gamemanager::Player;

class CharacterController {

  protected:
    std::unordered_map<std::string, IState *> stateDict{};
    IState *current = nullptr;
    Player *player = nullptr;
    CharacterEntity *entity = nullptr;
    std::queue<std::string> cmdStrings;
    std::queue<std::string> messages;

  public:
    virtual ~CharacterController() = default;

    void init(GameState *state, CharacterEntity *entity, Player *plyer);
    virtual void update() = 0;
    void add(std::string key, IState *state);
    void remove(std::string id);
    void change(std::string id);
    void setPlayer(Player *player);
    Player *getPlayer();
    void setCharacter(CharacterEntity *entity);
    CharacterEntity *getCharacter();
    void setCmdString(std::string cmd);
    std::string getCmdString();
    void setMsg(std::string arg);
    std::string getMsg();
    std::queue<std::string> getAllMsgs();
};
#endif // ADVENTURE2018_CHARACTERCONTROLLER_H
