#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/filesystem.hpp>
#include <fstream>

#include "logging.h"
#include "persistence/PersistenceService.h"

namespace fs = boost::filesystem;

namespace mudserver {

namespace persistence {

const std::string PersistenceService::PLAYERS_FILE = "players.dat";
const std::string PersistenceService::GAMESTATE_FILE = "gamestate.dat";

PersistenceService::PersistenceService(std::string configDir)
    : configDir{configDir} {};

void PersistenceService::save(PlayerService &ps) {
    auto logger = logging::getLogger("PersistenceService::save()");
    boost::system::error_code returnedError;
    fs::create_directories(configDir, returnedError);
    if (!returnedError) {
        fs::path file{PLAYERS_FILE};
        auto fullPath = configDir / file;

        if (fs::exists(fullPath)) {
            fs::remove(fullPath);
        }

        std::ofstream ofs{fullPath.generic_string()};
        boost::archive::text_oarchive oa{ofs};
        oa << ps;
        logger->info("Saved player service");
    }
}

PlayerService PersistenceService::loadPlayerService() {
    auto logger = logging::getLogger("PersistenceService::loadPlayerService");

    PlayerService ps{};

    boost::system::error_code returnedError;
    fs::path file{PLAYERS_FILE};
    auto fullPath = configDir / file;

    boost::filesystem::exists(fullPath, returnedError);
    if (!returnedError) {
        std::ifstream ifs{(configDir / file).generic_string()};
        try {
            boost::archive::text_iarchive ia{ifs};
            ia >> ps;
            logger->info("Loaded player service");
        } catch (const boost::archive::archive_exception &e) {
            logger->warning("Bad player save file");
        }
    }

    return ps;
}

void PersistenceService::save(GameState &gs) {
    auto logger = logging::getLogger("PersistenceService::save()");
    boost::system::error_code returnedError;
    fs::create_directories(configDir, returnedError);
    if (!returnedError) {
        fs::path file{GAMESTATE_FILE};
        auto fullPath = configDir / file;

        if (fs::exists(fullPath)) {
            fs::remove(fullPath);
        }

        std::ofstream ofs{fullPath.generic_string()};
        boost::archive::text_oarchive oa{ofs};
        oa << gs;
        logger->info("Saved game state");
    }
}
GameState PersistenceService::loadGameState() {
    auto logger = logging::getLogger("PersistenceService::loadGameState");

    GameState gs{};

    boost::system::error_code returnedError;
    fs::path file{GAMESTATE_FILE};
    auto fullPath = configDir / file;

    boost::filesystem::exists(fullPath, returnedError);
    if (!returnedError) {
        std::ifstream ifs{(configDir / file).generic_string()};
        try {
            boost::archive::text_iarchive ia{ifs};
            ia >> gs;
            logger->info("Loaded game state");
        } catch (const boost::archive::archive_exception &e) {
            logger->warning("Bad gamestate save file");
        }
    }

    return gs;
}

} // namespace persistence
} // namespace mudserver
