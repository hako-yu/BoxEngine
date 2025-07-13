#include "Logging/LogManager.h"
#include "Logging/ConsoleLogger.h"
#include <cassert>

FLogManager& FLogManager::GetInstance()
{
    static FLogManager Instance;
    return Instance;
}

void FLogManager::Initialize()
{
    if (!bInitialized)
    {
        // 默认使用控制台日志器
        Logger = std::make_shared<FConsoleLogger>();
        bInitialized = true;
    }
}

void FLogManager::Shutdown()
{
    if (bInitialized)
    {
        Logger.reset();
        bInitialized = false;
    }
}

void FLogManager::SetLogger(FLoggerPtr InLogger)
{
    assert(InLogger != nullptr);
    Logger = InLogger;
}

FLoggerPtr FLogManager::GetLogger() const
{
    return Logger;
}

void FLogManager::Log(ELogLevel Level, const FChar* Message)
{
    auto& Instance = GetInstance();
    if (Instance.Logger)
    {
        Instance.Logger->Log(Level, Message);
    }
}

void FLogManager::Log(ELogLevel Level, const FString& Message)
{
    Log(Level, Message.c_str());
}

void FLogManager::LogVerbose(const FChar* Message)
{
    Log(ELogLevel::Verbose, Message);
}

void FLogManager::LogInfo(const FChar* Message)
{
    Log(ELogLevel::Log, Message);
}

void FLogManager::LogWarning(const FChar* Message)
{
    Log(ELogLevel::Warning, Message);
}

void FLogManager::LogError(const FChar* Message)
{
    Log(ELogLevel::Error, Message);
}

void FLogManager::LogFatal(const FChar* Message)
{
    Log(ELogLevel::Fatal, Message);
}

void FLogManager::LogVerbose(const FString& Message)
{
    Log(ELogLevel::Verbose, Message);
}

void FLogManager::LogInfo(const FString& Message)
{
    Log(ELogLevel::Log, Message);
}

void FLogManager::LogWarning(const FString& Message)
{
    Log(ELogLevel::Warning, Message);
}

void FLogManager::LogError(const FString& Message)
{
    Log(ELogLevel::Error, Message);
}

void FLogManager::LogFatal(const FString& Message)
{
    Log(ELogLevel::Fatal, Message);
} 