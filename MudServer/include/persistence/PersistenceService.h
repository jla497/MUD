#ifndef PERSISTENCE_SERVICE_H
#define PERSISTENCE_SERVICE_H

#include <boost/filesystem.hpp>
#include <string>

#include "gamemanager/GameState.h"
#include "gamemanager/PlayerService.h"

namespace mudserver {
namespace persistence {

using mudserver::gamemanager::GameState;
using mudserver::gamemanager::PlayerService;

class PersistenceService {
  private:
    boost::filesystem::path configDir;

    const static std::string PLAYERS_FILE;
    const static std::string GAMESTATE_FILE;

  public:
    explicit PersistenceService(std::string configDir);
    void save(PlayerService &ps);
    void save(PlayerService &ps, std::string fileName);
    void save(GameState &gs);

    PlayerService loadPlayerService();
    PlayerService loadPlayerService(std::string fileName);
    GameState loadGameState();
};

} // namespace persistence
} // namespace mudserver

#endif // PERSISTENCE_SERVICE_H
