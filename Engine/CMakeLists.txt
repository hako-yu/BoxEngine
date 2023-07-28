set(ENGINE_ROOT_DIR "${BE_ROOT_DIR}/Engine")

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS ${CMAKE_SOURCE_DIR})
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Launch)
endif()

add_subdirectory(Source/Runtime/Platform)
add_subdirectory(Source/Runtime/Core)

add_subdirectory(Source/Runtime/Render/RHI)
add_subdirectory(Source/Runtime/Render/D3D12RHI)
add_subdirectory(Source/Runtime/Render/RenderCore)

add_subdirectory(Source/Runtime/Engine)
add_subdirectory(Source/Editor/EditorMain)

add_subdirectory(Source/Runtime/Launch)
