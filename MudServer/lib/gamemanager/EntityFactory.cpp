#include "gamemanager/EntityFactory.h"

namespace mudserver {
namespace gamemanager {

	void EntityFactory::initNpcLUT(YamlParser& parser) {
	   auto npcs= parser.getAllNPCS();
	   LutBuilder lutBuilder;
	   npcLookUp = lutBuilder.createNpcLUT(npcs);
	}
	
	NonPlayerCharacter EntityFactory::buildNpc(Id id) {
		
		return npcLookUp.find(id)->second;
	}
}
}

