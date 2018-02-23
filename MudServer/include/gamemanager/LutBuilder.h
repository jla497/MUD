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

using std::unique_ptr;
using std::unordered_map;
using roomId = unsigned int;
using Id = unsigned int;
class LutBuilder {
  public:
    std::map<roomId, RoomEntity *>
    createLUT(std::deque<unique_ptr<RoomEntity>> &mVector);
    std::map<Id, NonPlayerCharacter>
    createNpcLUT(std::vector<std::unique_ptr<NonPlayerCharacter>> &mVector);
};

} // namespace gamemanager
} // namespace mudserver
#endif // GAMESTATE_H
