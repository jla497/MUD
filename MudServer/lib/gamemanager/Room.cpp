#include "gamemanager/Room.h"

namespace mudserver {
namespace gamemanager {

Room::Room() {}

Room::Room(RoomID id) :
    id{id} {}

RoomID Room::getID() const {
    return id;
}

}  // namespace gamemanager
}  // namespace mudserver
