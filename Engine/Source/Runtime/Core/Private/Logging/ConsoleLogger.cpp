#include "Logging/ConsoleLogger.h"
#include <chrono>
#include <iomanip>
#include <sstream>

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#endif

FConsoleLogger::FConsoleLogger()
{
    LogInfo("Console Logger initialized");
}

void FConsoleLogger::Log(ELogLevel Level, const FChar* Message)
{
    std::lock_guard<std::mutex> Lock(LogMutex);
    
    FString FormattedMessage = FormatLogMessage(Level, Message);
    
    // 输出到控制台
    std::cout << FormattedMessage << std::endl;
    
    // Windows平台下同时输出到调试器
#ifdef PLATFORM_WINDOWS
    OutputDebugStringA(FormattedMessage.c_str());
    OutputDebugStringA("\n");
#endif
}

void FConsoleLogger::Log(ELogLevel Level, const FString& Message)
{
    Log(Level, Message.c_str());
}

FString FConsoleLogger::FormatLogMessage(ELogLevel Level, const FChar* Message)
{
    auto Now = std::chrono::system_clock::now();
    auto TimeT = std::chrono::system_clock::to_time_t(Now);
    auto Tm = *std::localtime(&TimeT);
    
    std::stringstream SS;
    SS << std::put_time(&Tm, "%Y-%m-%d %H:%M:%S");
    
    std::stringstream Result;
    Result << "[" << SS.str() << "] [" << GetLogLevelString(Level) << "] " << Message;
    
    return Result.str();
} 