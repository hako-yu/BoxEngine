cmake_minimum_required(VERSION 3.27)

project(BoxEngine VERSION 1.0.0)

# Param
set(BOX_ENGINE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(BOX_ENGINE_SHADER ${BOX_ENGINE_ROOT}/Shader)
set(BOX_ENGINE_SOURCE ${BOX_ENGINE_ROOT}/Source)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)

# Macro
# add_compile_definitions(UNICODE)
add_compile_definitions(SHADER_ROOT_PATH=L"${BOX_ENGINE_SHADER}")

# Source
add_subdirectory(${BOX_ENGINE_SOURCE}/Logging)
add_subdirectory(${BOX_ENGINE_SOURCE}/Core)
add_subdirectory(${BOX_ENGINE_SOURCE}/Rendering/RHI)
add_subdirectory(${BOX_ENGINE_SOURCE}/Rendering/Renderer)
add_subdirectory(${BOX_ENGINE_SOURCE}/Launcher)

# VS config
set_directory_properties(PROPERTIES VS_STARTUP_PROJECT Launcher)
