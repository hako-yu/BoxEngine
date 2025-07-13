#pragma once

#include "Types.h"

enum class ELogLevel : FInt32
{
    Verbose = 0,
    Log = 1,
    Warning = 2,
    Error = 3,
    Fatal = 4
};

// 日志级别字符串转换
inline const FChar* GetLogLevelString(ELogLevel Level)
{
    switch (Level)
    {
    case ELogLevel::Verbose: return "VERBOSE";
    case ELogLevel::Log: return "LOG";
    case ELogLevel::Warning: return "WARNING";
    case ELogLevel::Error: return "ERROR";
    case ELogLevel::Fatal: return "FATAL";
    default: return "UNKNOWN";
    }
} 