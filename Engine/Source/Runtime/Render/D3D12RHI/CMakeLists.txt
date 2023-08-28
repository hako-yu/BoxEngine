
include(${BE_ROOT_DIR}/Cmake/ModuleRules.cmake)

implement_module(D3D12RHI)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Engine/Source/Runtime/Render")

target_link_libraries(${TARGET_NAME} PRIVATE d3dcompiler)
target_link_libraries(${TARGET_NAME} PRIVATE D3D12)
target_link_libraries(${TARGET_NAME} PRIVATE dxgi)

add_public_dependency_module(RHI)


set(SHADER_ROOT_DIR L"${ENGINE_ROOT_DIR}/Shaders")

target_compile_definitions(
    D3D12RHI
        PUBLIC
            D3D12_SUPPORTS
            SHADER_ROOT_DIR=${SHADER_ROOT_DIR}
)
# message(WARNING ${SHADER_ROOT_DIR})
