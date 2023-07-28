
include(${BE_ROOT_DIR}/Cmake/ModuleRules.cmake)

implement_module(D3D12RHI)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Engine/Source/Runtime/Render")

# target_link_libraries(${TARGET_NAME} PRIVATE D3D12)

add_public_dependency_module(RHI)
