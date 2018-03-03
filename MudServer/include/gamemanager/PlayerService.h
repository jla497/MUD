#ifndef PLAYERSERVICE_H
#define PLAYERSERVICE_H

#include "Player.h"
#include "entities/CharacterEntity.h"

#include <boost/bimap.hpp>
#include <boost/optional.hpp>
#include <unordered_map>

#include <boost/serialization/access.hpp>
#include <boost/serialization/unordered_map.hpp>

namespace mudserver {
namespace gamemanager {

using PcBmType = boost::bimap<PlayerId, UniqueId>;

enum class AddPlayerResult {
    playerAdded,
    playerExists,
    playerInvalid,
    _NUM_RESULTS_
};

class PlayerService {
private:
    PlayerId nextPlayerId;
    std::unordered_map<PlayerId, Player> players;
    std::unordered_map<UsernameType, PlayerId> playerIdByName;
    std::unordered_map<networking::ConnectionId, PlayerId> playerIdByConnection;
    PcBmType playerCharacterBimap;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar &nextPlayerId;
        ar &players;
        ar &playerIdByName;
        //ar &playerCharacterBimap;
    }

    PlayerId getNextPlayerId();

  public:
    PlayerService();
    boost::optional<Player &> getPlayerById(PlayerId playerId);
    PlayerId getPlayerIdByName(const UsernameType &username);
    boost::optional<Player &>
    getPlayerByConnection(networking::ConnectionId connectionId);
    networking::ConnectionId setPlayerConnection(PlayerId playerId);
    void setPlayerConnection(PlayerId playerId,
                             networking::ConnectionId connectionId);
    boost::optional<Player &> identify(UsernameType username,
                                       PasswordType password);
    AddPlayerResult addPlayer(UsernameType username, PasswordType password);

    /**
     * Given a player's id, return the player's character's id.
     * @param playerId the player's id
     * @return the player's character id (may be null)
     */
    const UniqueId *playerToCharacter(PlayerId playerId);

    /**
     * Given a character's id, return the character's player's id.
     * @param characterId the character's id
     * @return the character's player id
     */
    PlayerId characterToPlayer(UniqueId characterId);

    /**
     * Create and add a new player character to the game state.
     * @param playerId the player's id
     */
    CharacterEntity createPlayerCharacter(PlayerId playerId);
    networking::ConnectionId getPlayerConnection(PlayerId playerId);
};

} // namespace gamemanager
} // namespace mudserver

#endif // PLAYERSERVICE_H
