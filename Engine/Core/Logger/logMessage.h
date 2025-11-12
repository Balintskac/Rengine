#pragma once
#include <string>
#include <chrono>
#include <sstream>

enum class LogLevel {
    Trace, Debug, Info, Warn, Error, Fatal
};

struct LogMessage {
    LogLevel level;
    std::string category;
    std::string message;
    std::chrono::system_clock::time_point timestamp;
};
