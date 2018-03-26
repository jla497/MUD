#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <boost/bimap.hpp>
#include <chrono>
#include <memory>
#include <queue>
#include <unordered_map>

#include "GameState.h"
#include "Player.h"
#include "PlayerService.h"
#include "UniqueId.h"
#include "actions/Action.h"
#include "commandparser/CommandParser.h"
#include "connectionmanager/ConnectionManager.h"
#include "entities/CharacterEntity.h"
#include "entities/Entity.h"
#include "persistence/PersistenceService.h"
#include "observe/ActionObserver.h"

namespace mudserver {
namespace gamemanager {

constexpr std::chrono::milliseconds DEFAULT_TICK_LENGTH_MS{1000};

using mudserver::commandparser::CommandParser;

/**
 * The game manager is in charge of carrying out the main game loop. As a
 * result, it has access to game state and the networking layer, as we need to
 * interact with these during the game loop. It owns Players (this may change
 * in the future). It has a queue of outgoing messages and a queue of unapplied
 * actions. It fetches batches of incoming messages from the network.
 */
class GameManager {
    constexpr static auto &PLEASE_LOGIN =
        u8"Please login/register using identify <username> <password>\n";
    constexpr static auto &LOGIN_SUCCESS = u8"Logged in successfully\n";
    constexpr static auto &INCORRECT_IDENT =
        u8"Incorrect username and/or password\n";

    GameState &gameState;
    std::chrono::milliseconds tick = DEFAULT_TICK_LENGTH_MS;
    bool done = false;
    CommandParser commandParser;
    connection::ConnectionManager &connectionManager;
    persistence::PersistenceService &persistenceService;

    PlayerService playerService;
    std::queue<connection::gameAndUserInterface> outgoingMessages;
    std::queue<std::unique_ptr<Action>> actionsA;
    std::queue<std::unique_ptr<Action>> actionsB;
    std::queue<std::unique_ptr<Action>> *currentAQueuePtr;
    std::queue<std::unique_ptr<Action>> *nextAQueuePtr;
    std::vector<CharacterController *> controllerQueue;

    /**
     * Process a collection of messages from the server, taking various actions
     * as required.
     * @param messages the messages
     */
    void
    processMessages(std::vector<connection::gameAndUserInterface> &messages);
    /**
     * Given a connection (network layer concept), put a message on the queue
     * for that connection.
     * @param conn the connection
     * @param msg the message
     */
    void enqueueMessage(networking::Connection conn, std::string msg);
    /**
     * Process the outgoing message queue, passing messages along to players.
     */
    void sendMessagesToPlayers();

    /**
     * Given an action, put it on the pending action queue
     * @param action the action to enqueue
     */
    void enqueueAction(std::unique_ptr<Action> action);
    /**
     * Process the pending action queue, calling execute() on each action.
     */
    void performQueuedActions();

    Player *getPlayerFromLogin(const connection::gameAndUserInterface &message);

  public:
    /**
     * The GameManager is constructed with references to a ConnectionManager and
     * a GameState. These should both be owned in the same or higher scope as
     * the GameManager itself.
     * @param connMan the connection manager
     * @param gameState the game state
     * @param persistenceService the persistence service for saving game
     */
    GameManager(connection::ConnectionManager &connMan, GameState &gameState,
                persistence::PersistenceService &persistenceService);

    /**
     * The main game loop. Updates game state once per tick, processes messages
     * constantly.
     */
    void mainLoop();
    void haltServer();

    /**
     * Gets a reference to the game state.
     * @return the game state
     */
    GameState &getState();

    /**
     * Send a message to a given character. This will translate to sending a
     * a message to that character's player, but callers are expected to be
     * at the world-level, not the user-level
     * @param characterId the id of the character
     * @param message the message to send
     */

    /**
     * Swap two player's characters
     * @param playerId1 the player's id
     * @param playerId2 the player's id
     */
    void swapCharacters(UniqueId initCharacterId, UniqueId targetCharacterId);

    void sendCharacterMessage(UniqueId characterId, std::string message);
    PlayerService &getPlayerService();
    void persistData();
    void loadPersistedData();

    void swapQueuePtrs();
    void addActionToQueue(std::unique_ptr<Action> action);

    void fetchCntrlCmds(ActionObserver *observer);
};

} // namespace gamemanager
} // namespace mudserver

#endif
