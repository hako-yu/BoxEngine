
include(${BE_ROOT_DIR}/Cmake/ModuleRules.cmake)

implement_module(EditorMain)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Engine/Source/Editor")

add_public_dependency_module(Core)
