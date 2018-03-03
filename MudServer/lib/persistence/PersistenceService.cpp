#include "persistence/PersistenceService.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/filesystem.hpp>
#include "logging.h"

namespace fs = boost::filesystem;

namespace mudserver {

namespace persistence {

PersistenceService::PersistenceService(std::string configDir) :
    configDir{configDir} {};

void PersistenceService::save(PlayerService &ps) {
    boost::system::error_code returnedError;
    fs::create_directories( configDir, returnedError );
    if (!returnedError) {
        fs::path file{"players.dat"};
        auto fullPath = configDir / file;

        if (fs::exists(fullPath)) {
            fs::remove(fullPath);
        }

        std::ofstream ofs{fullPath.generic_string()};
        boost::archive::text_oarchive oa{ofs};
        oa << ps;
    }
}
PlayerService PersistenceService::loadPlayerService() {
    auto logger = logging::getLogger("PersistenceService::loadPlayerService");

    PlayerService ps{};

    boost::system::error_code returnedError;
    fs::path file{"players.dat"};
    auto fullPath = configDir / file;

    boost::filesystem::exists(fullPath, returnedError);
    if (!returnedError) {
        std::ifstream ifs{(configDir / file).generic_string()};
        try {
            boost::archive::text_iarchive ia{ifs};
            ia >> ps;
        } catch (const boost::archive::archive_exception &e) {
            logger->warning("Bad player save file");
        }
    }

    return ps;
}

} // namespace mudserver
} // namespace persistence
