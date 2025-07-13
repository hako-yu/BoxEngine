#pragma once

#include "Logging/ILogger.h"
#include <iostream>
#include <mutex>

class FConsoleLogger : public ILogger
{
public:
    FConsoleLogger();
    virtual ~FConsoleLogger() = default;
    
    virtual void Log(ELogLevel Level, const FChar* Message) override;
    virtual void Log(ELogLevel Level, const FString& Message) override;
    
private:
    std::mutex LogMutex;
    FString FormatLogMessage(ELogLevel Level, const FChar* Message);
}; 