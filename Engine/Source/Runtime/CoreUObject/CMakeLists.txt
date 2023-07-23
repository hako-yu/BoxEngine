
include(${BE_ROOT_DIR}/Cmake/ModuleRules.cmake)

implement_module(CoreUObject)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Engine/Source/Runtime")

add_public_dependency_module(Core)
