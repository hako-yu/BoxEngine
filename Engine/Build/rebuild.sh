#!/bin/bash

echo "========================================"
echo "BoxEngine Rebuild Script for Unix/Linux"
echo "========================================"

# 设置脚本目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# 阶段1: 清理
echo
echo "[Stage 1/2] Cleaning previous build..."
echo "========================================"
"$SCRIPT_DIR/clean.sh" nopause
if [ $? -ne 0 ]; then
    echo "Error: Clean stage failed."
    exit 1
fi
echo "Clean completed successfully."

# 阶段2: 重新构建
echo
echo "[Stage 2/2] Rebuilding project..."
echo "========================================"
"$SCRIPT_DIR/build.sh" nopause
if [ $? -ne 0 ]; then
    echo "Error: Build stage failed."
    exit 1
fi

echo
echo "========================================"
echo "Rebuild completed successfully!"
echo "========================================"
echo
echo "Intermediate files location: $SCRIPT_DIR/../Intermediate"
echo "Executable location: $SCRIPT_DIR/../Binaries/Launcher"
echo 