#ifndef LUTBUILD_H
#define LUTBUILD_H

#include <boost/bimap.hpp>
#include <deque>
#include <memory>
#include <unordered_map>

#include "Player.h"
#include "UniqueId.h"
#include "entities/AreaEntity.h"
#include "entities/DoorEntity.h"
#include "entities/Entity.h"
#include "entities/NonPlayerCharacter.h"
#include "entities/ObjectEntity.h"
#include "entities/PlayerCharacter.h"
#include "entities/RoomEntity.h"
#include "entities/ShopEntity.h"
namespace mudserver {
namespace gamemanager {

using roomId = unsigned int;
using Id = unsigned int;
class LutBuilder {
  public:

    std::map<Id, NonPlayerCharacter>
    createNpcLUT(std::vector<NonPlayerCharacter> &mVector);
    std::unordered_map<roomId, RoomEntity>
    createLUT(std::deque<RoomEntity> &mVector);
};

} // namespace gamemanager
} // namespace mudserver
#endif // GAMESTATE_H
