#include "logging.h"
#include "ConsoleLogger.h"

namespace mudserver {
namespace logging {

static LogLevel logLevel = LogLevel::info;

std::unique_ptr<ILogger> getLogger() {
    return std::make_unique<ConsoleLogger>("", logLevel);
}
std::unique_ptr<ILogger> getLogger(const std::string &identifier) {
    return std::make_unique<ConsoleLogger>(identifier, logLevel);
}

void setLogLevel(LogLevel level) { logLevel = level; }

} // namespace logging
} // namespace mudserver