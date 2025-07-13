# Launcher模块配置
set(MODULE_NAME Launcher)

# 收集源文件
file(GLOB_RECURSE PRIVATE_SOURCES 
    "Private/*.cpp"
    "Private/*.h"
)

file(GLOB_RECURSE PUBLIC_SOURCES 
    "Public/*.cpp"
    "Public/*.h"
)

# 创建可执行文件
add_executable(${MODULE_NAME}
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

# 链接Core模块
target_link_libraries(${MODULE_NAME} Core)

# 设置编译选项
target_compile_definitions(${MODULE_NAME} PRIVATE
    LAUNCHER_MODULE=1
)

# Windows平台特定设置
if(PLATFORM_WINDOWS)
    target_link_libraries(${MODULE_NAME} 
        user32
        gdi32
        winmm
        kernel32
    )
    
    # 设置Windows子系统
    set_target_properties(${MODULE_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# 设置输出名称
set_target_properties(${MODULE_NAME} PROPERTIES
    OUTPUT_NAME "${MODULE_NAME}"
) 