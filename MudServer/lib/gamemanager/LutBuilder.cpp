
#include "gamemanager/LutBuilder.h"
#include <boost/algorithm/string.hpp>

namespace mudserver {
namespace gamemanager {

std::unordered_map<roomId, RoomEntity>
LutBuilder::createLUT(std::deque<RoomEntity> &rooms) {
    std::unordered_map<roomId, RoomEntity> map;
    for (auto &room : rooms) {
        map[room.getId()] = room;
    }
    return map;
}

std::map<Id, CharacterEntity>
LutBuilder::createNpcLUT(std::vector<CharacterEntity> &npcs) {
    std::map<Id, CharacterEntity> map;
    for (auto &npc : npcs) {
        map[npc.getTypeId()] = npc;
    }
    return map;
}

std::map<Id, ObjectEntity>
LutBuilder::createObjectLUT(std::vector<ObjectEntity> &objects) {
    std::map<Id, ObjectEntity> map;
    for (auto &obj : objects) {
        map[obj.getObjectTypeId()] = obj;
    }
    return map;
}

std::map<spellName, Spell>
LutBuilder::createSpellLUT(std::vector<Spell> &spells) {
    std::map<spellName, Spell> map;
    Spell swapSpell;
    swapSpell.setName("body swap");
    swapSpell.setType(Spell::SpellType::swap);
    map[swapSpell.getName()] = swapSpell;

    Spell decoySpell;
    decoySpell.setName("decoy");
    decoySpell.setType(Spell::SpellType::decoy);
    map[decoySpell.getName()] = decoySpell;
    
    for (auto &spell : spells) {
        map[boost::to_lower_copy(spell.getName())] = spell;
    }
    return map;
}

} // namespace gamemanager
} // namespace mudserver
