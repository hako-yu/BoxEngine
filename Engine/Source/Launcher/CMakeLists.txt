set(TARGET_NAME Launcher)

file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

add_executable(
    ${TARGET_NAME}
    ${HEADER_FILES} ${SOURCE_FILES}
)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_include_directories(
    ${TARGET_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

# Link
# target_link_libraries(
#     ${TARGET_NAME}
#     PUBLIC
# )

target_link_libraries(
    ${TARGET_NAME}
    PRIVATE Logging Renderer
)
