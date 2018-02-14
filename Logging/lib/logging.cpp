#include "logging.h"
#include "ConsoleLogger.h"

namespace mudserver {
namespace logging {

static LogLevel logLevel = LogLevel::info;

/*
 * FIXME
 * FIXME
 * FIXME
 *
 * no. no no no no no no no no no.
 *
 * you're making a new logger EVERY TIME YOU WANT TO PRINT SOMETHING.
 * terrible.
 * please stop.
 */

std::unique_ptr<ILogger> getLogger() {
    return std::make_unique<ConsoleLogger>("", logLevel);
}

std::unique_ptr<ILogger> getLogger(const std::string& identifier) {
    return std::make_unique<ConsoleLogger>(identifier, logLevel);
}

void setLogLevel(LogLevel level) { logLevel = level; }

}  // namespace logging
}  // namespace mudserver