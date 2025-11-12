#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include "ILoggerSink.h"

class Logger {
public:
    static Logger& Get() {
        static Logger instance;
        return instance;
    }

    void AddSink(std::shared_ptr<ILoggerSink> sink) {
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_Sinks.push_back(sink);
    }

    void Log(LogLevel level, const std::string& category, const std::string& message) {
        LogMessage msg{ level, category, message, std::chrono::system_clock::now() };
        std::lock_guard<std::mutex> lock(m_Mutex);
        for (auto& sink : m_Sinks)
            sink->Write(msg);
    }

private:
    Logger() = default;
    std::vector<std::shared_ptr<ILoggerSink>> m_Sinks;
    std::mutex m_Mutex;
};
