#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <boost/foreach.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <memory>
#include <unordered_map>
#include <deque>

#include "entities/AreaEntity.h"
#include "entities/PlayerCharacter.h"
//#include "Room.h"
#include "gamemanager/LutBuilder.h"
#include "YamlParser.h"
#include "UniqueId.h"

namespace mudserver {
namespace gamemanager {

using namespace boost::bimaps;

using std::unique_ptr;
using std::unordered_map;
using std::deque;
using std::vector;

using CharacterRoomLookupTable = bimap<set_of<UniqueId>, list_of<roomId>> ;
using RoomLookupTable = std::unordered_map<roomId, RoomEntity*> ;
using CharacterLookUp = std::map<UniqueId, unique_ptr<PlayerCharacter>> ;

/**
 * The overarching idea of GameState is that it should
 *      - be owned by the GameManager
 *      - own all the information required to save/serialize a game
 *      - be the source of truth for all state relating to the world
 */
class GameState {

    CharacterRoomLookupTable characterRoomLookUp;
    RoomLookupTable roomLookUp;
    CharacterLookUp characterLookUp;
    deque<unique_ptr<AreaEntity>> areas;
    YamlParser parser;
    std::unique_ptr<AreaEntity> area;

public:

    GameState() = default;

    void initFromYaml(std::string filename);
    void parseYamlFile(std::string string);
    void initRoomLUT();

    void addAreaFromParser();
    void addCharacter(unique_ptr<PlayerCharacter> character);
    void addCharacterRoomRelationToLUT(UniqueId characterId,
                                       unsigned int roomId);
    void addRoomToLUT(RoomEntity*);
    AreaEntity* getAreaFromParser();
    deque<unique_ptr<AreaEntity>>& getAreas();
    vector<UniqueId> getCharactersInRoom(RoomEntity* room);
    PlayerCharacter* getCharacterFromLUT(UniqueId id);
    RoomEntity* getCharacterLocation(PlayerCharacter* character);
    RoomEntity* getCharacterLocation(PlayerCharacter& character);
    RoomEntity* getRoomFromLUT(const roomId);
    void clearAreas();
    void clearCharacterRoomLUT();
    void printLut(std::string str);

    };

}  // namespace gamemanager
}  // namespace mudserver
#endif  // GAMESTATE_H
