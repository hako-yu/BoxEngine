
include(${BE_ROOT_DIR}/Cmake/ModuleRules.cmake)

implement_module(Platform)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Engine/Source/Runtime")

target_compile_definitions(Platform PUBLIC PLATFORM_WINDOWS)
