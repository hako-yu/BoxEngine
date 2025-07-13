cmake_minimum_required(VERSION 3.27)
project(BoxEngine VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置UTF-8编码
if(MSVC)
    # MSVC编译器UTF-8设置
    add_compile_options(/utf-8)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    # GCC/Clang编译器UTF-8设置
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

# 平台检测
if(WIN32)
    set(PLATFORM_WINDOWS TRUE)
    add_definitions(-DPLATFORM_WINDOWS)
elseif(APPLE)
    set(PLATFORM_MACOS TRUE)
    add_definitions(-DPLATFORM_MACOS)
elseif(UNIX)
    set(PLATFORM_LINUX TRUE)
    add_definitions(-DPLATFORM_LINUX)
endif()

# 添加子目录
add_subdirectory(Source/Runtime/Core)
add_subdirectory(Source/Runtime/Launcher) 