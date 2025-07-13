@echo off
setlocal enabledelayedexpansion

echo ========================================
echo BoxEngine Rebuild Script for Windows
echo ========================================

:: 设置脚本目录
set SCRIPT_DIR=%~dp0

:: 阶段1: 清理
echo.
echo [Stage 1/2] Cleaning previous build...
echo ========================================
call "%SCRIPT_DIR%clean.bat" nopause
if %errorlevel% neq 0 (
    echo Error: Clean stage failed.
    pause
    exit /b 1
)
echo Clean completed successfully.

:: 阶段2: 重新构建
echo.
echo [Stage 2/2] Rebuilding project...
echo ========================================
call "%SCRIPT_DIR%build.bat" nopause
if %errorlevel% neq 0 (
    echo Error: Build stage failed.
    pause
    exit /b 1
)

echo.
echo ========================================
echo Rebuild completed successfully!
echo ========================================
echo.
echo Intermediate files location: %SCRIPT_DIR%..\Intermediate
echo Executable location: %SCRIPT_DIR%..\Binaries\Release\Launcher.exe
echo.

pause 