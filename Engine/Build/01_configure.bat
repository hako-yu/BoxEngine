@echo off
setlocal enabledelayedexpansion

echo ========================================
echo BoxEngine Configuration Stage
echo ========================================

:: 检查CMake是否安装
where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: CMake not found. Please install CMake 3.27 or later.
    pause
    exit /b 1
)

:: 检查Visual Studio是否安装
where cl >nul 2>nul
if %errorlevel% neq 0 (
    echo Warning: Visual Studio compiler not found in PATH.
    echo Please run this script from Visual Studio Developer Command Prompt.
    echo.
)

:: 设置构建目录
set BUILD_DIR=%~dp0..\Intermediate
set BINARIES_DIR=%~dp0..\Binaries

:: 创建构建目录
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
if not exist "%BINARIES_DIR%" mkdir "%BINARIES_DIR%"

:: 设置CMake生成器
set CMAKE_GENERATOR=Visual Studio 17 2022
set CMAKE_ARCH=x64

:: 检查Visual Studio版本
where cl >nul 2>nul
if %errorlevel% equ 0 (
    :: 使用默认生成器
    set CMAKE_GENERATOR=
)

:: 配置项目
echo.
echo Configuring project...
cd /d "%BUILD_DIR%"

if "%CMAKE_GENERATOR%"=="" (
    cmake -G "%CMAKE_GENERATOR%" -A %CMAKE_ARCH% "%~dp0.."
) else (
    cmake "%~dp0.."
)

if %errorlevel% neq 0 (
    echo Error: CMake configuration failed.
    pause
    exit /b 1
)

echo Configuration completed successfully. 