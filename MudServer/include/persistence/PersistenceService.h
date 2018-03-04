#ifndef PERSISTENCE_SERVICE_H
#define PERSISTENCE_SERVICE_H

#include <boost/filesystem.hpp>
#include <string>

#include "gamemanager/PlayerService.h"
#include "gamemanager/GameState.h"

namespace mudserver {
namespace persistence {

using mudserver::gamemanager::PlayerService;
using mudserver::gamemanager::GameState;

class PersistenceService {
  private:
    boost::filesystem::path configDir;

    const static std::string PLAYERS_FILE;
    const static std::string GAMESTATE_FILE;

  public:
    explicit PersistenceService(std::string configDir);
    void save(PlayerService &ps);
    void save(GameState &gs);

    PlayerService loadPlayerService();
    GameState loadGameState();
};

} // namespace persistence
} // namespace mudserver

#endif // PERSISTENCE_SERVICE_H