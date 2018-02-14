#ifndef MUDSERVER_LOGGING_H
#define MUDSERVER_LOGGING_H

#include <memory>
#include <string>

namespace mudserver {
namespace logging {

enum class LogLevel { debug, info, warning, error };

//FIXME why are we using 'pretend' string_views? use the real ones
using StrView = const std::string&;

class ILogger {
public:
    virtual ~ILogger() = default;
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
