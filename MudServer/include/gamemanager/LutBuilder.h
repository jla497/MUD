#ifndef LUTBUILD_H
#define LUTBUILD_H

#include <boost/bimap.hpp>
#include <deque>
#include <memory>
#include <unordered_map>

#include "Player.h"
#include "UniqueId.h"
#include "entities/Entity.h"
#include "entities/RoomEntity.h"

namespace mudserver {
namespace gamemanager {

using roomId = unsigned int;

class LutBuilder {
  public:
    std::unordered_map<roomId, RoomEntity>
    createLUT(std::deque<RoomEntity> &mVector);
};

} // namespace gamemanager
} // namespace mudserver
#endif // GAMESTATE_H
