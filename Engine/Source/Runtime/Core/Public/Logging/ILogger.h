#pragma once

#include "LogLevel.h"
#include <memory>

class ILogger
{
public:
    virtual ~ILogger() = default;
    
    virtual void Log(ELogLevel Level, const FChar* Message) = 0;
    virtual void Log(ELogLevel Level, const FString& Message) = 0;
    
    // 便捷方法
    virtual void LogVerbose(const FChar* Message) { Log(ELogLevel::Verbose, Message); }
    virtual void LogInfo(const FChar* Message) { Log(ELogLevel::Log, Message); }
    virtual void LogWarning(const FChar* Message) { Log(ELogLevel::Warning, Message); }
    virtual void LogError(const FChar* Message) { Log(ELogLevel::Error, Message); }
    virtual void LogFatal(const FChar* Message) { Log(ELogLevel::Fatal, Message); }
    
    virtual void LogVerbose(const FString& Message) { Log(ELogLevel::Verbose, Message); }
    virtual void LogInfo(const FString& Message) { Log(ELogLevel::Log, Message); }
    virtual void LogWarning(const FString& Message) { Log(ELogLevel::Warning, Message); }
    virtual void LogError(const FString& Message) { Log(ELogLevel::Error, Message); }
    virtual void LogFatal(const FString& Message) { Log(ELogLevel::Fatal, Message); }
};

using FLoggerPtr = FSharedPtr<ILogger>; 