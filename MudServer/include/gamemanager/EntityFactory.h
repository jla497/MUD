#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <boost/foreach.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <memory>
#include <map>
#include <deque>

#include "entities/ShopEntity.h"
#include "entities/AreaEntity.h"
#include "entities/DoorEntity.h"
#include "entities/NonPlayerCharacter.h"
#include "entities/ObjectEntity.h"
#include "entities/RoomEntity.h"
#include "entities/PlayerCharacter.h"
#include "gamemanager/LutBuilder.h"

#include "UniqueId.h"


namespace mudserver {
namespace gamemanager {
  using NpcLookUp = std::map<Id, NonPlayerCharacter>;
  using NpcVector = std::vector<std::unique_ptr<NonPlayerCharacter>>;
  

  class EntityFactory {
    
    NpcLookUp npcLookUp;
    NpcVector npcs;
public:
   EntityFactory(NpcVector npcs);
   void init();

	NonPlayerCharacter buildNpc(Id id);
  
  };
}  // namespace gamemanager
}



#endif