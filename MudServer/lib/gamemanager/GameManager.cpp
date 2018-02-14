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

GameManager::GameManager(connection::ConnectionManager& connMan,
                         GameState& gameState)
    : gameState{gameState},
      connectionManager{connMan}
{}

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

    auto startTime = clock::now();

    while (!done) {
        if (connectionManager.update()) {
            // An error was encountered, stop
            done = true;
            continue;
        }
    
        auto messages = connectionManager.sendToGameManager();

        processMessages(messages);

        auto delta = clock::now() - startTime;
        if (delta >= tick) {
            startTime = clock::now();
            performQueuedActions();
            sendMessagesToPlayers();
        }

    }
}

void GameManager::processMessages(std::vector<connection::gameAndUserInterface>& messages) {
    static auto logger = logging::getLogger("GameManager::processMessages");
  
    for (const auto& message : messages) {

        // look up player from ID
        auto playerId = message.conn.id;
        logger->debug(std::to_string(playerId) + ": " + message.text);

        if (players.find(playerId) == players.end()) {
            // We should add a login service that can deal with
            //      - players not existing
            //      - authenticating players
            players[playerId] = {playerId, "player" + std::to_string(playerId), ""};
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

        // parse message into verb/object
        auto action = commandParser.actionFromPlayerCommand(
            playerCharacter, message.text, *this);

        std::stringstream retMessage;
        retMessage << "DEBUG: " << *action;

        enqueueAction(std::move(action));

        enqueueMessage(message.conn, retMessage.str());
    }
}

void GameManager::enqueueMessage(networking::Connection conn, std::string msg) {
    outgoingMessages.push({std::move(msg), conn});
}

void GameManager::sendMessagesToPlayers() {
    std::vector<connection::gameAndUserInterface> toSend;
    toSend.reserve(outgoingMessages.size());



    while (!outgoingMessages.empty()) {
        toSend.push_back(outgoingMessages.front());
        outgoingMessages.pop();
    }
    connectionManager.receiveFromGameManager(toSend);
    connectionManager.sendToServer();
}

void GameManager::enqueueAction(std::unique_ptr<Action> action) {
    actions.push(std::move(action));
}

void GameManager::performQueuedActions() {
    while (!actions.empty()) {
        actions.front()->execute();
        actions.pop();
    }
}

GameState &GameManager::getState() {
    return gameState;
}

void GameManager::sendCharacterMessage(UniqueId characterId, std::string message) {
    enqueueMessage({characterIdToPlayer(characterId).getId()}, std::move(message));
}

// TODO: Factor out into a new class
// Technical debt alert:
// I believe the player-character mapping is complex enough to factor out into
// a new class - possibly will be the LoginManager once we get that far


PlayerCharacter* GameManager::playerIdToCharacter(PlayerId playerId) {
    auto entry = playerCharacterBimap.left.find(playerId);
    if (entry != playerCharacterBimap.left.end()) {
        auto characterId = entry->second;
        return gameState.getCharacterFromLUT(characterId);
    }

    return nullptr;
}

PlayerCharacter* GameManager::playerToCharacter(const Player& player) {
    return playerIdToCharacter(player.getId());
}

Player& GameManager::characterToPlayer(const PlayerCharacter& character) {
    return characterIdToPlayer(character.getEntityId());
}

Player& GameManager::characterIdToPlayer(UniqueId characterId) {
    auto playerId = playerCharacterBimap.right.find(characterId)->second;
    return players.at(playerId);
}

void GameManager::addPlayerCharacter(PlayerId playerId) {
    auto testShortDesc = "TestPlayerName" + std::to_string(playerCharacterBimap.size());

    PlayerCharacter pc(pc::ARMOR, std::string{pc::DAMAGE}, std::vector<std::string>{}, pc::EXP,
            pc::GOLD, std::string{pc::HIT}, std::vector<std::string>{}, pc::LEVEL,
            std::vector<std::string>{}, testShortDesc, pc::THAC0);

    playerCharacterBimap.insert(PcBmType::value_type(playerId, pc.getEntityId()));
    gameState.addCharacter(pc);
}

}  // namespace gamemanager
}  // namespace mudserver
