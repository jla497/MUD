#ifndef PERSISTENCE_SERVICE_H
#define PERSISTENCE_SERVICE_H

#include <string>
#include <boost/filesystem.hpp>

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

    PlayerService loadPlayerService();
};

}
}

#endif // PERSISTENCE_SERVICE_H