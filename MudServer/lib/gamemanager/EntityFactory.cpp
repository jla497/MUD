#include "gamemanager/EntityFactory.h"

namespace mudserver {
namespace gamemanager {
using namespace mudserver::resources::commands;

EntityFactory::EntityFactory(NpcVector npcs, ObjectVector objects)
    : objects(objects), npcs(npcs) {}

void EntityFactory::init() {
    LutBuilder lutBuilder;
    npcLookUp = lutBuilder.createNpcLUT(npcs);
    objectLookUp = lutBuilder.createObjectLUT(objects);
}

CharacterEntity EntityFactory::buildNpc(Id id) {
    return npcLookUp.find(id)->second;
}

ObjectEntity EntityFactory::buildObject(Id id) {
    return objectLookUp.find(id)->second;
}

void EntityFactory::modifyCharacter(CharacterEntity *entity, attributeMap map) {
    if (map.find(CGOLD) != map.end()) {
        auto gold = stoi(map.find(CGOLD)->second);
        if (gold < 0)
            entity->subtractGold((gold * -1));
        else
            entity->addGold((unsigned int)gold);
    }
    if (map.find(CEXP) != map.end()) {
        auto newExp = stoi(map.find(CEXP)->second);
        auto curExp = entity->getExp();
        if (curExp < newExp) {
            entity->incExp((unsigned int)(newExp - curExp));
        }
    }
    std::cout << "entity gold: " << entity->getGold()
              << " entity exp: " << entity->getExp() << std::endl;
}
} // namespace gamemanager
} // namespace mudserver
