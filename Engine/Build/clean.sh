#!/bin/bash

echo "========================================"
echo "BoxEngine Clean Script for Unix/Linux"
echo "========================================"

# 检查参数
NOPAUSE=0
if [ "$1" = "nopause" ]; then
    NOPAUSE=1
fi

# 设置目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
INTERMEDIATE_DIR="$SCRIPT_DIR/../Intermediate"
BINARIES_DIR="$SCRIPT_DIR/../Binaries"

echo "Cleaning build artifacts..."

# 清理中间产物
if [ -d "$INTERMEDIATE_DIR" ]; then
    echo "Removing Intermediate directory..."
    rm -rf "$INTERMEDIATE_DIR"
    if [ $? -eq 0 ]; then
        echo "Successfully removed Intermediate directory."
    else
        echo "Warning: Failed to remove Intermediate directory."
    fi
else
    echo "Intermediate directory not found."
fi

# 清理最终产物
if [ -d "$BINARIES_DIR" ]; then
    echo "Removing Binaries directory..."
    rm -rf "$BINARIES_DIR"
    if [ $? -eq 0 ]; then
        echo "Successfully removed Binaries directory."
    else
        echo "Warning: Failed to remove Binaries directory."
    fi
else
    echo "Binaries directory not found."
fi

echo
echo "Clean completed successfully!"
echo

if [ $NOPAUSE -eq 0 ]; then
    read -p "Press Enter to continue..."
fi 