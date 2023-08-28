set(ENGINE_ROOT_DIR "${BE_ROOT_DIR}/Engine")

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS ${CMAKE_SOURCE_DIR})
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Launch)
endif()

# Source
# Core
add_subdirectory(Source/Runtime/Platform)
add_subdirectory(Source/Runtime/Core)

# RHI
add_subdirectory(Source/Runtime/Render/RHI)
add_subdirectory(Source/Runtime/Render/D3D12RHI)
add_subdirectory(Source/Runtime/Render/RHICore)

# Renderer
add_subdirectory(Source/Runtime/Render/Renderer)
add_subdirectory(Source/Runtime/Render/RenderCore)

# Engine
add_subdirectory(Source/Runtime/Engine)
add_subdirectory(Source/Editor/EditorMain)

# Launch
add_subdirectory(Source/Runtime/Launch)
