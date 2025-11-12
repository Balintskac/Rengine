#pragma once
#include "LogMessage.h"

class ILoggerSink {
public:
    virtual ~ILoggerSink() = default;
    virtual void Write(const LogMessage& message) = 0;
};