#!/bin/bash

echo "========================================"
echo "BoxEngine Post-Processing Stage"
echo "========================================"

# 设置构建目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/../Intermediate"
BINARIES_DIR="$SCRIPT_DIR/../Binaries"

# 检查构建目录是否存在
if [ ! -d "$BUILD_DIR" ]; then
    echo "Error: Build directory not found. Please run configuration and compilation stages first."
    exit 1
fi

# 后处理阶段 - 拷贝构建产物到Binaries目录
echo
echo "Post-processing: Copying build artifacts to Binaries directory..."
cd "$BUILD_DIR"

# 创建Binaries目录
mkdir -p "$BINARIES_DIR"

# 查找并拷贝构建产物
echo "Searching for build artifacts..."

# 查找可执行文件
EXECUTABLE=$(find . -name "Launcher" -type f 2>/dev/null | head -1)
if [ -n "$EXECUTABLE" ]; then
    echo "Found executable: $EXECUTABLE"
    cp "$EXECUTABLE" "$BINARIES_DIR/"
    if [ $? -eq 0 ]; then
        echo "Successfully copied Launcher to Binaries directory."
    else
        echo "Error: Failed to copy Launcher."
    fi
else
    echo "Warning: Launcher executable not found."
fi

# 查找库文件
LIBRARY=$(find . -name "libCore.a" -o -name "Core.lib" 2>/dev/null | head -1)
if [ -n "$LIBRARY" ]; then
    echo "Found library: $LIBRARY"
    cp "$LIBRARY" "$BINARIES_DIR/"
    if [ $? -eq 0 ]; then
        echo "Successfully copied library to Binaries directory."
    else
        echo "Error: Failed to copy library."
    fi
else
    echo "Warning: Core library not found."
fi

echo "Post-processing completed successfully." 