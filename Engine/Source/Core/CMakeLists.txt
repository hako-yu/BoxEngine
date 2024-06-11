set(TARGET_NAME Core)

file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

add_library(
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
