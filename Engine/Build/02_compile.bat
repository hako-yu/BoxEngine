@echo off
setlocal enabledelayedexpansion

echo ========================================
echo BoxEngine Compilation Stage
echo ========================================

:: 设置构建目录
set BUILD_DIR=%~dp0..\Intermediate

:: 检查构建目录是否存在
if not exist "%BUILD_DIR%" (
    echo Error: Build directory not found. Please run configuration stage first.
    pause
    exit /b 1
)

:: 构建项目
echo.
echo Building project...
cd /d "%BUILD_DIR%"

cmake --build . --config Release

if %errorlevel% neq 0 (
    echo Error: Build failed.
    pause
    exit /b 1
)

echo Compilation completed successfully. 