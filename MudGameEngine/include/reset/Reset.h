#ifndef RESET_H
#define RESET_H
#include <string>
#include <unordered_map>
#include <vector>

#include "entities/AreaEntity.h"
#include "entities/DoorEntity.h"
#include "entities/NonPlayerCharacter.h"
#include "entities/ObjectEntity.h"
#include "entities/RoomEntity.h"
#include "entities/ShopEntity.h"
#include "gamemanager/EntityFactory.h"
#include "logging.h"

// forward declaration
namespace mudserver {
namespace gamemanager {
class GameState;
}
} // namespace mudserver

struct findNpc {
    explicit findNpc(int id) : id(id) {}
    bool operator()(const std::unique_ptr<NonPlayerCharacter> &ptr) {
        return static_cast<int>(ptr->getNpcTypeId()) == id;
    }

  private:
    int id;
};

class Reset {
    enum class ResetKeyword {
        undefined,
        object,
        npc,
        door,
        equip,
        give,
        resets
    };

    static std::unordered_map<std::string, ResetKeyword> resetLookUp;

  public:
    Reset() = default;
    Reset(int id, const std::string &action, const std::string &comment, const std::string &state,
          int slot, int limit, int roomID);

    void execute(mudserver::gamemanager::GameState &state);

    std::string getAction();

    int getTypeId();

    int getRoomId();

    int getLimit();

  private:
    // TODO: figure out Id, it seems that Id may refer to different things
    // depending on the reset action.
    // If the action is equip, than it is talking about the object with the id.
    int id{};
    // maybe change action from string to its own type
    std::string action;
    std::string comment;
    std::string state;
    int slot{};
    int limit{};
    int roomID{};

    void resetNpc(mudserver::gamemanager::GameState &state);
};
#endif
