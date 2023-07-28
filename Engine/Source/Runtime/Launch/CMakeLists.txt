
include(${BE_ROOT_DIR}/Cmake/ModuleRules.cmake)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

add_compile_definitions(
    PLATFORM_WINDOWS
    D3D12_SUPPORTS
)

implement_primary_module(Launch)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Engine/Source/Runtime")

add_public_dependency_module(Platform)
add_public_dependency_module(Core)
add_public_dependency_module(Engine)
add_public_dependency_module(EditorMain)
