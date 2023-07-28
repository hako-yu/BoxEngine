
include(${BE_ROOT_DIR}/Cmake/ModuleRules.cmake)

implement_module(D3D12RHI)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Engine/Source/Runtime/Render")

add_public_dependency_module(RHI)

target_compile_definitions(D3D12RHI PUBLIC D3D12_SUPPORTS)
