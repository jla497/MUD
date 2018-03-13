//
// Created by jla497 on 01/03/18.
//

#ifndef ADVENTURE2018_RESETMANAGER_H
#define ADVENTURE2018_RESETMANAGER_H

#include <map>
#include <vector>

#include "reset/Reset.h"

namespace mudserver {
namespace gamemanager {
class GameState;
}
} // namespace mudserver

class ResetManager {
    std::vector<Reset> resets;

    std::vector<CharacterEntity>
    populateNpcs(int limit, int npcTypeId,
                 mudserver::gamemanager::GameState *state);
    void equipNpcs(const ObjectEntity &object, std::vector<CharacterEntity> &entities);
    void addNpcsToRooms(std::vector<CharacterEntity> &entities, int roomId,
                        mudserver::gamemanager::GameState *state);
    int getNumOfNpcsInRoom(int roomId, int npcTypeId,
                           mudserver::gamemanager::GameState *state);

  public:
    explicit ResetManager(const std::vector<Reset> &resets);
    void applyResets(mudserver::gamemanager::GameState *state);
};
#endif // ADVENTURE2018_RESETMANAGER_H
