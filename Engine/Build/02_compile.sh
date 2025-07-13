#!/bin/bash

echo "========================================"
echo "BoxEngine Compilation Stage"
echo "========================================"

# 设置构建目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/../Intermediate"

# 检查构建目录是否存在
if [ ! -d "$BUILD_DIR" ]; then
    echo "Error: Build directory not found. Please run configuration stage first."
    exit 1
fi

# 构建项目
echo
echo "Building project..."
cd "$BUILD_DIR"

make -j$(nproc)

if [ $? -ne 0 ]; then
    echo "Error: Build failed."
    exit 1
fi

echo "Compilation completed successfully." 