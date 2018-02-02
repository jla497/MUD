#ifndef ROOM_H
#define ROOM_H

#include <boost/cstdint.hpp>

namespace mudserver {
namespace gamemanager {

using RoomID = uintptr_t;

class Room {
    RoomID id;

public:
    Room(RoomID id);
    RoomID getID() const;
};


}  // namespace gamemanager
}  // namespace mudserver

#endif  // ROOM_H
