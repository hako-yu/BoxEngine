
include(${BE_ROOT_DIR}/Cmake/ModuleRules.cmake)

implement_module(Engine)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Engine/Source/Runtime")

add_public_dependency_module(Platform)
add_public_dependency_module(Core)

add_public_dependency_module(RenderCore)
add_public_dependency_module(Renderer)
