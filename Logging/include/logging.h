#ifndef MUDSERVER_LOGGING_H
#define MUDSERVER_LOGGING_H

#include <memory>
#include <string>

namespace mudserver {
namespace logging {

using StrView = const std::string&;

enum class LogLevel { debug, info, warning, error };

class ILogger {
public:
    virtual void debug(StrView str) = 0;
    virtual void info(StrView str) = 0;
    virtual void warning(StrView str) = 0;
    virtual void error(StrView str) = 0;
};

void setLogLevel(LogLevel level);
std::unique_ptr<ILogger> getLogger();
std::unique_ptr<ILogger> getLogger(const std::string& identifier);

}  // namespace logging

}  // namespace mudserver

#endif  // MUDSERVER_LOGGING_H
