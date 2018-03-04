#ifndef PERSISTENCE_SERVICE_H
#define PERSISTENCE_SERVICE_H

#include <boost/filesystem.hpp>
#include <string>

#include "gamemanager/PlayerService.h"

namespace mudserver {
namespace persistence {

using mudserver::gamemanager::PlayerService;

class PersistenceService {
  private:
    boost::filesystem::path configDir;

  public:
    explicit PersistenceService(std::string configDir);
    void save(PlayerService &ps);
    void save(PlayerService &ps, std::string fileName);

    PlayerService loadPlayerService();
};

} // namespace persistence
} // namespace mudserver

#endif // PERSISTENCE_SERVICE_H