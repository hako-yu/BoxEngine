
macro(declare_module module_name)
    set(TARGET_NAME ${module_name})
    file(GLOB_RECURSE HEADER_FILES "*.h")
    file(GLOB_RECURSE SOURCE_FILES "*.cpp")
    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})
endmacro()


macro(implement_module module_name)

    declare_module(${module_name})

    add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

    target_include_directories(
        ${TARGET_NAME}
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/Public)

    target_include_directories(
        ${TARGET_NAME}
        PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/Private)

endmacro()


macro(implement_primary_module module_name)

    declare_module(${module_name})

    add_executable(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})
    
    target_include_directories(
        ${TARGET_NAME}
        PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/Public)

    target_include_directories(
        ${TARGET_NAME}
        PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/Private)

endmacro()



function(add_public_dependency_module module_name)
    target_link_libraries(${TARGET_NAME} PUBLIC ${module_name})
endfunction()

function(add_private_dependency_module module_name)
    target_link_libraries(${TARGET_NAME} PRIVATE ${module_name})
endfunction()
