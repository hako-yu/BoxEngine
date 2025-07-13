#!/bin/bash

echo "========================================"
echo "BoxEngine Build Script for Unix/Linux"
echo "========================================"

# 检查参数
NOPAUSE=0
if [ "$1" = "nopause" ]; then
    NOPAUSE=1
fi

# 设置脚本目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# 阶段1: 配置
echo
echo "[Stage 1/3] Configuration"
echo "========================================"
"$SCRIPT_DIR/01_configure.sh"
if [ $? -ne 0 ]; then
    echo "Error: Configuration stage failed."
    if [ $NOPAUSE -eq 0 ]; then
        read -p "Press Enter to continue..."
    fi
    exit 1
fi

# 阶段2: 编译
echo
echo "[Stage 2/3] Compilation"
echo "========================================"
"$SCRIPT_DIR/02_compile.sh"
if [ $? -ne 0 ]; then
    echo "Error: Compilation stage failed."
    if [ $NOPAUSE -eq 0 ]; then
        read -p "Press Enter to continue..."
    fi
    exit 1
fi

# 阶段3: 后处理
echo
echo "[Stage 3/3] Post-Processing"
echo "========================================"
"$SCRIPT_DIR/03_postprocess.sh"
if [ $? -ne 0 ]; then
    echo "Error: Post-processing stage failed."
    if [ $NOPAUSE -eq 0 ]; then
        read -p "Press Enter to continue..."
    fi
    exit 1
fi

echo
echo "========================================"
echo "Build completed successfully!"
echo "========================================"
echo
echo "Intermediate files location: $SCRIPT_DIR/../Intermediate"
echo "Executable location: $SCRIPT_DIR/../Binaries/Launcher"
echo

if [ $NOPAUSE -eq 0 ]; then
    read -p "Press Enter to continue..."
fi 