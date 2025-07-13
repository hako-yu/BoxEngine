#pragma once

#include <cstdint>
#include <memory>
#include <string>

// 基础类型定义
using FInt8 = int8_t;
using FUInt8 = uint8_t;
using FInt16 = int16_t;
using FUInt16 = uint16_t;
using FInt32 = int32_t;
using FUInt32 = uint32_t;
using FInt64 = int64_t;
using FUInt64 = uint64_t;

using FFloat = float;
using FDouble = double;

using FChar = char;
using FWChar = wchar_t;

using FString = std::string;
using FWString = std::wstring;

// 智能指针类型
template<typename T>
using FUniquePtr = std::unique_ptr<T>;

template<typename T>
using FSharedPtr = std::shared_ptr<T>;

template<typename T>
using FWeakPtr = std::weak_ptr<T>;

// 平台相关类型
#ifdef PLATFORM_WINDOWS
    using FWindowHandle = void*; // HWND
    using FModuleHandle = void*; // HMODULE
#elif defined(PLATFORM_MACOS)
    using FWindowHandle = void*; // NSWindow*
    using FModuleHandle = void*; // CFBundleRef
#elif defined(PLATFORM_LINUX)
    using FWindowHandle = void*; // Window
    using FModuleHandle = void*; // void*
#endif

// 引擎核心类型
struct FVector2D
{
    FFloat X;
    FFloat Y;
    
    FVector2D() : X(0.0f), Y(0.0f) {}
    FVector2D(FFloat InX, FFloat InY) : X(InX), Y(InY) {}
};

struct FVector3D
{
    FFloat X;
    FFloat Y;
    FFloat Z;
    
    FVector3D() : X(0.0f), Y(0.0f), Z(0.0f) {}
    FVector3D(FFloat InX, FFloat InY, FFloat InZ) : X(InX), Y(InY), Z(InZ) {}
};

struct FVector4D
{
    FFloat X;
    FFloat Y;
    FFloat Z;
    FFloat W;
    
    FVector4D() : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f) {}
    FVector4D(FFloat InX, FFloat InY, FFloat InZ, FFloat InW) : X(InX), Y(InY), Z(InZ), W(InW) {}
};

struct FColor
{
    FUInt8 R;
    FUInt8 G;
    FUInt8 B;
    FUInt8 A;
    
    FColor() : R(0), G(0), B(0), A(255) {}
    FColor(FUInt8 InR, FUInt8 InG, FUInt8 InB, FUInt8 InA = 255) : R(InR), G(InG), B(InB), A(InA) {}
};

// 引擎常量
namespace EngineConstants
{
    constexpr FInt32 MaxWindowTitleLength = 256;
    constexpr FInt32 MaxLogMessageLength = 1024;
    constexpr FInt32 DefaultWindowWidth = 1280;
    constexpr FInt32 DefaultWindowHeight = 720;
} 