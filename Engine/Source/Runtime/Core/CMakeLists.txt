# Core模块配置
set(MODULE_NAME Core)

# 收集源文件
file(GLOB_RECURSE PRIVATE_SOURCES 
    "Private/*.cpp"
    "Private/*.h"
)

file(GLOB_RECURSE PUBLIC_SOURCES 
    "Public/*.cpp"
    "Public/*.h"
)

# 创建静态库
add_library(${MODULE_NAME} STATIC
    ${PRIVATE_SOURCES}
    ${PUBLIC_SOURCES}
)

# 设置包含目录
target_include_directories(${MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_include_directories(${MODULE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

# 设置编译选项
target_compile_definitions(${MODULE_NAME} PRIVATE
    CORE_MODULE=1
)

# 设置输出名称
set_target_properties(${MODULE_NAME} PROPERTIES
    OUTPUT_NAME "${MODULE_NAME}"
) 