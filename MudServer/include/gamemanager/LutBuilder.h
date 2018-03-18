#ifndef LUTBUILD_H
#define LUTBUILD_H

#include <boost/bimap.hpp>
#include <deque>
#include <memory>
#include <unordered_map>
#include <string>

#include "Player.h"
#include "UniqueId.h"
#include "entities/AreaEntity.h"
#include "entities/CharacterEntity.h"
#include "entities/DoorEntity.h"
#include "entities/Entity.h"
#include "entities/ObjectEntity.h"
#include "entities/RoomEntity.h"
#include "entities/ShopEntity.h"
#include "Spell.h"
namespace mudserver {
namespace gamemanager {

using roomId = unsigned int;
using Id = unsigned int;
using spellName = std::string;

class LutBuilder {
  public:
    std::map<Id, CharacterEntity>
    createNpcLUT(std::vector<CharacterEntity> &mVector);
    std::map<Id, ObjectEntity>
    createObjectLUT(std::vector<ObjectEntity> &mVector);
    std::unordered_map<roomId, RoomEntity>
    createLUT(std::deque<RoomEntity> &mVector);
    std::map<spellName, Spell> 
    createSpellLUT(std::vector<Spell> &mVector);
};

} // namespace gamemanager
} // namespace mudserver
#endif // GAMESTATE_H
