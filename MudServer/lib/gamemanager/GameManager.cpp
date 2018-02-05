#include <boost/format.hpp>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>
#include <vector>

#include "connectionmanager/ConnectionManager.h"
#include "entities/PlayerCharacter.h"
#include "gamemanager/GameManager.h"
#include "logging.h"
#include "resources/PlayerCharacterDefaults.h"

namespace mudserver {
namespace gamemanager {

namespace pc = mudserver::resources::playercharacter;

using boost::format;
using boost::str;
using std::vector;

GameManager::GameManager(connection::ConnectionManager& connMan)
    : connectionManager{connMan},
      gameState(),
      commandParser(),
      tick{DEFAULT_TICK_LENGTH_MS},
      done{false},
      players(),
      outgoingMessages(),
      actions() {}

/**
 * Runs a standard game loop, which consists of the following steps:
 *      - get user input (messages from the server)
 *      - update the game state using the input
 *      - render, i.e. send broadcast messages to players.
 */
void GameManager::mainLoop() {
    static auto logger = logging::getLogger("GameManager::mainLoop");
    logger->info("Entered main game loop");

    using clock = std::chrono::high_resolution_clock;

    while (!done) {
        auto startTime = clock::now();
        unique_ptr<gameAndUserMsgs> messagesForConnMan;

        if (connectionManager.update()) {
            // An error was encountered, stop
            done = true;
            continue;
        }

        auto messages = connectionManager.sendToGameManager();

        processMessages(*messages);

        performQueuedActions();

        sendMessagesToPlayers();

        auto delta = startTime - clock::now();

        if (tick > delta) {
            std::this_thread::sleep_for(tick - delta);
        } else {
            logger->warning(str(format("%s %d %s") %
                                "Game loop length exceeded tick time of" %
                                tick.count() % "ms"));
        }
    }
}

void GameManager::processMessages(gameAndUserMsgs& messages) {
    static auto logger = logging::getLogger("GameManager::processMessages");
    for (auto& message : messages) {
        // look up player from ID
        auto playerId = message->conn.id;
        logger->debug(std::to_string(playerId) + ": " + message->text);

        if (players.find(playerId) == players.end()) {
            // We should add a login service that can deal with
            //      - players not existing
            //      - authenticating players
            players.emplace(
                playerId,
                Player{playerId, "player" + std::to_string(playerId), ""});
        }

        // Guaranteed not to throw out_of_range - Player has been created
        auto player = players.at(playerId);

        // look up player's character
        // pointer is used as player may not have character yet

        auto character = playerToCharacter(player);
        if (!character) {
            // create a new character for the player and add it to the game
            // state
            addPlayerCharacter(playerId);
        }
        auto& playerCharacter = *playerToCharacter(player);

        // auto room = gameState.getCharacterLocation(character);

        // parse message into verb/object
        std::unique_ptr<Action> action = commandParser.actionFromPlayerCommand(
            playerCharacter, message->text, *this);

        std::stringstream retMessage;
        retMessage << *action;

        enqueueAction(std::move(action));

        enqueueMessage(message->conn, retMessage.str());
    }
}

void GameManager::enqueueMessage(networking::Connection conn, std::string msg) {
    outgoingMessages.push({std::move(msg), conn});
}

void GameManager::sendMessagesToPlayers() {
    auto toSend = std::make_unique<gameAndUserMsgs>();

    while (!outgoingMessages.empty()) {
        toSend->push_back(std::make_unique<connection::gameAndUserInterface>(
            outgoingMessages.front()));
        outgoingMessages.pop();
    }
    connectionManager.receiveFromGameManager(std::move(toSend));
    connectionManager.sendToServer();
}

void GameManager::enqueueAction(unique_ptr<Action> action) {
    actions.push(std::move(action));
}
void GameManager::performQueuedActions() {
    while (!actions.empty()) {
        actions.front()->execute();
        actions.pop();
    }
}
GameState& GameManager::getState() { return gameState; }

void GameManager::sendCharacterMessage(UniqueId characterId,
                                       std::string message) {
    auto player = characterIdToPlayer(characterId);
    auto conn = networking::Connection{player.getId()};
    enqueueMessage(conn, std::move(message));
}

// TODO: Factor out into a new class
// Technical debt alert:
// I believe the player-character mapping is complex enough to factor out into
// a new class - possibly will be the LoginManager once we get that far

PlayerCharacter* GameManager::playerToCharacter(const Player& player) {
    return playerIdToCharacter(player.getId());
}

PlayerCharacter* GameManager::playerIdToCharacter(PlayerId playerId) {
    auto entry = playerCharacterBimap.left.find(playerId);
    if (entry != playerCharacterBimap.left.end()) {
        auto characterId = entry->second;
        return gameState.getCharacterFromLUT(characterId);
    }

    return nullptr;
}

Player& GameManager::characterToPlayer(const PlayerCharacter& character) {
    return characterIdToPlayer(character.getEntityId());
}

Player& GameManager::characterIdToPlayer(UniqueId characterId) {
    auto playerId = playerCharacterBimap.right.find(characterId)->second;
    return players.at(playerId);
}

void GameManager::addPlayerCharacter(PlayerId playerId) {
    auto character = std::make_unique<PlayerCharacter>(
        pc::ARMOR, std::string{pc::DAMAGE}, std::vector<std::string>{}, pc::EXP,
        pc::GOLD, std::string{pc::HIT}, std::vector<std::string>{}, pc::LEVEL,
        std::vector<std::string>{}, std::string{}, pc::THAC0);

    playerCharacterBimap.insert(
        PcBmType::value_type(playerId, character->getEntityId()));
    gameState.addCharacter(std::move(character));
}

}  // namespace gamemanager
}  // namespace mudserver
