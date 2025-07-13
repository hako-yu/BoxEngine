#!/bin/bash

echo "========================================"
echo "BoxEngine Configuration Stage"
echo "========================================"

# 检查CMake是否安装
if ! command -v cmake &> /dev/null; then
    echo "Error: CMake not found. Please install CMake 3.27 or later."
    exit 1
fi

# 检查编译器
if command -v g++ &> /dev/null; then
    COMPILER="g++"
elif command -v clang++ &> /dev/null; then
    COMPILER="clang++"
else
    echo "Error: No C++ compiler found. Please install g++ or clang++."
    exit 1
fi

echo "Using compiler: $COMPILER"

# 设置构建目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/../Intermediate"
BINARIES_DIR="$SCRIPT_DIR/../Binaries"

# 创建构建目录
mkdir -p "$BUILD_DIR"
mkdir -p "$BINARIES_DIR"

# 配置项目
echo
echo "Configuring project..."
cd "$BUILD_DIR"

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER="$COMPILER" "$SCRIPT_DIR/.."

if [ $? -ne 0 ]; then
    echo "Error: CMake configuration failed."
    exit 1
fi

echo "Configuration completed successfully." 