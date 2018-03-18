#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <boost/bimap.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <deque>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Spell.h"
#include "SpellParser.h"
#include "UniqueId.h"
#include "YamlParser.h"
#include "entities/AreaEntity.h"
#include "entities/CharacterEntity.h"
#include "entities/DoorEntity.h"
#include "gamemanager/LutBuilder.h"
#include "reset/Reset.h"
#include "reset/ResetManager.h"

class Reset;
namespace mudserver {
namespace gamemanager {

using namespace boost::bimaps;

struct UniqueIdHash {
  public:
    std::size_t operator()(UniqueId id) const;
};

/**
 * The overarching idea of GameState is that it should
 *      - be owned by the GameManager
 *      - own all the information required to save/serialize a game
 *      - be the source of truth for all state relating to the world
 */
class GameState {
  private:
    bimap<set_of<UniqueId>, list_of<roomId>> characterRoomLookUp;
    std::unordered_map<roomId, RoomEntity> roomLookUp;
    std::unordered_map<UniqueId, CharacterEntity, UniqueIdHash> characterLookUp;
    std::map<spellName, Spell> spellLookUp;
    std::deque<AreaEntity> areas;
    YamlParser areaParser;
    AreaEntity area;
    std::unique_ptr<EntityFactory> factory;
    std::vector<Spell> spells;
    SpellParser spellParser;

    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        (void)version;
        ar &characterLookUp;
        ar &characterRoomLookUp;
    }

  public:
    void initFromYaml(std::vector<std::string> areaFilenames,
                      std::vector<std::string> spellFilenames);

    void parseAreaYamlFile(std::string string);
    void initRoomLUT();
    void addAreaFromParser();

    void initSpellLUT();
    void parseSpellYamlFile(std::string filename);
    void addSpellsFromParser();

    void addCharacter(CharacterEntity &character);
    void addCharacterRoomRelationToLUT(UniqueId characterId,
                                       unsigned int roomId);
    void addRoomToLUT(const RoomEntity &room);
    AreaEntity getAreaFromParser();
    std::deque<AreaEntity> &getAreas();
    std::vector<Spell> &getSpells();
    std::vector<UniqueId> getCharactersInRoom(RoomEntity *room);
    CharacterEntity *getCharacterFromLUT(UniqueId id);
    void addCharacter(CharacterEntity &character, Id roomID);
    RoomEntity *getCharacterLocation(const CharacterEntity &character);
    RoomEntity *getRoomFromLUT(const roomId);
    void clearAreas();
    void removeCharacterByUniqueId(UniqueId characterId);
    void clearCharacterRoomLUT();
    EntityFactory &getFactory();
    void doReset();

    Spell *getSpellByName(const spellName name);
    void killCharacter(const CharacterEntity &character);
};

} // namespace gamemanager
} // namespace mudserver
#endif // GAMESTATE_H
