#ifndef MUDSERVER_LOGGER_H
#define MUDSERVER_LOGGER_H

#include <ostream>
#include <string>

#include "logging.h"

namespace mudserver {
namespace logging {

class ConsoleLogger : public ILogger {
    std::string identifier;
    std::string identifiedLog(StrView str);
    LogLevel level;

public:
    ConsoleLogger(std::string identifier, LogLevel level);
    void debug(StrView str) override;
    void info(StrView str) override;
    void warning(StrView str) override;
    void error(StrView str) override;
};

}  // namespace logging
}  // namespace mudserver

#endif  // MUDSERVER_LOGGER_H
