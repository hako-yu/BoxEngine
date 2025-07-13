#pragma once

#include "ILogger.h"
#include <memory>

class FLogManager
{
public:
    static FLogManager& GetInstance();
    
    void Initialize();
    void Shutdown();
    
    void SetLogger(FLoggerPtr Logger);
    FLoggerPtr GetLogger() const;
    
    // 便捷的日志方法
    static void Log(ELogLevel Level, const FChar* Message);
    static void Log(ELogLevel Level, const FString& Message);
    
    static void LogVerbose(const FChar* Message);
    static void LogInfo(const FChar* Message);
    static void LogWarning(const FChar* Message);
    static void LogError(const FChar* Message);
    static void LogFatal(const FChar* Message);
    
    static void LogVerbose(const FString& Message);
    static void LogInfo(const FString& Message);
    static void LogWarning(const FString& Message);
    static void LogError(const FString& Message);
    static void LogFatal(const FString& Message);

private:
    FLogManager() = default;
    ~FLogManager() = default;
    FLogManager(const FLogManager&) = delete;
    FLogManager& operator=(const FLogManager&) = delete;
    
    FLoggerPtr Logger;
    bool bInitialized = false;
};

// 便捷宏定义
#define LOG_VERBOSE(Message) FLogManager::LogVerbose(Message)
#define LOG_INFO(Message) FLogManager::LogInfo(Message)
#define LOG_WARNING(Message) FLogManager::LogWarning(Message)
#define LOG_ERROR(Message) FLogManager::LogError(Message)
#define LOG_FATAL(Message) FLogManager::LogFatal(Message) 