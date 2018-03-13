//
// Created by jla497 on 11/03/18.
//

#ifndef ADVENTURE2018_CHARACTERCONTROLLER_H
#define ADVENTURE2018_CHARACTERCONTROLLER_H

#include <unordered_map>

class IState;
class CharacterEntity;

namespace mudserver{
    namespace gamemanager {
        class GameState;
    }
}

using mudserver::gamemanager::GameState;

class CharacterController {

protected:
std::unordered_map<std::string, IState*> stateDict{};
IState* current = nullptr;

public:
void init(GameState &state, CharacterEntity &entity);
virtual void update() = 0;
void add(std::string key, IState *state);
void remove(std::string id);
void change(std::string id);
};
#endif //ADVENTURE2018_CHARACTERCONTROLLER_H
