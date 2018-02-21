#include "gamemanager/EntityFactory.h"

namespace mudserver {
namespace gamemanager {

  EntityFactory::EntityFactory(NpcVector npcs): npcs(std::move(npcs)) {
  }

  void EntityFactory::init() {
  	LutBuilder lutBuilder;
	npcLookUp = lutBuilder.createNpcLUT(npcs);
  }

	
	NonPlayerCharacter EntityFactory::buildNpc(Id id) {
		return npcLookUp.find(id)->second;
	}
}
}

