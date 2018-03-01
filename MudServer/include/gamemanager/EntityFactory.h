#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <boost/bimap.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/foreach.hpp>
#include <deque>
#include <map>
#include <memory>

#include "UniqueId.h"
#include "entities/AreaEntity.h"
#include "entities/DoorEntity.h"
#include "entities/ObjectEntity.h"
#include "entities/CharacterEntity.h"
#include "entities/RoomEntity.h"
#include "entities/ShopEntity.h"
#include "gamemanager/LutBuilder.h"
#include "resources/commands.h"

namespace mudserver {
namespace gamemanager {
using NpcLookUp = std::map<Id, CharacterEntity>;
using NpcVector = std::vector<CharacterEntity>;
using attributeMap = std::unordered_map<std::string, std::string>;
class EntityFactory {
    NpcLookUp npcLookUp;
    NpcVector npcs;

  public:
    EntityFactory(NpcVector npcs);
    void init();

    CharacterEntity buildNpc(Id id);

    void modifyCharacter(CharacterEntity *entity, attributeMap map);
};
} // namespace gamemanager
}

#endif