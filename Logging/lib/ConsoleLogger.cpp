#include <iostream>

#include "ConsoleLogger.h"

namespace mudserver {
namespace logging {

ConsoleLogger::ConsoleLogger(std::string identifier, LogLevel level)
    : identifier{std::move(identifier)}, level{level} {}

void ConsoleLogger::debug(StrView str) {
    if (level == LogLevel::debug) {
        std::cout << "[DEBUG] " << identifiedLog(str) << std::endl;
    }
}

void ConsoleLogger::info(StrView str) {
    if (level <= LogLevel::info) {
        std::cout << "[INFO] " << identifiedLog(str) << std::endl;
    }
}

void ConsoleLogger::warning(StrView str) {
    if (level <= LogLevel::warning) {
        std::cout << "[WARN] " << identifiedLog(str) << std::endl;
    }
}

void ConsoleLogger::error(StrView str) {
    if (level <= LogLevel::error) {
        std::cout << "[ERROR] " << identifiedLog(str) << std::endl;
    }
}

std::string ConsoleLogger::identifiedLog(StrView str) {
    return identifier + ": " + str;
}

} // namespace logging
} // namespace mudserver
