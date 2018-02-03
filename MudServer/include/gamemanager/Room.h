#ifndef ROOM_H
#define ROOM_H

#include <boost/cstdint.hpp>

namespace mudserver {
namespace gamemanager {

using RoomID = int;

class Room {
    RoomID id;

public:
    Room();
    Room(RoomID id);
    RoomID getID() const;
};


}  // namespace gamemanager
}  // namespace mudserver

#endif  // ROOM_H
