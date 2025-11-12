#pragma once
#include "ILoggerSink.h"
#include <iostream>

class ConsoleSink : public ILoggerSink {
public:
    void Write(const LogMessage& msg) override {
        std::cout << "[" << ToString(msg.level) << "] "
                  << msg.category << ": " << msg.message << std::endl;
    }

private:
    std::string ToString(LogLevel level) const {
        switch (level) {
            case LogLevel::Trace: return "TRACE";
            case LogLevel::Debug: return "DEBUG";
            case LogLevel::Info:  return "INFO";
            case LogLevel::Warn:  return "WARN";
            case LogLevel::Error: return "ERROR";
            case LogLevel::Fatal: return "FATAL";
        }
        return "UNKNOWN";
    }
};
