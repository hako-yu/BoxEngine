@echo off
setlocal enabledelayedexpansion

echo ========================================
echo BoxEngine Build Script for Windows
echo ========================================

:: 检查参数
set "NOPAUSE=0"
if "%1"=="nopause" set "NOPAUSE=1"

:: 设置脚本目录
set SCRIPT_DIR=%~dp0

:: 阶段1: 配置
echo.
echo [Stage 1/3] Configuration
echo ========================================
call "%SCRIPT_DIR%01_configure.bat"
if %errorlevel% neq 0 (
    echo Error: Configuration stage failed.
    if %NOPAUSE%==0 pause
    exit /b 1
)

:: 阶段2: 编译
echo.
echo [Stage 2/3] Compilation
echo ========================================
call "%SCRIPT_DIR%02_compile.bat"
if %errorlevel% neq 0 (
    echo Error: Compilation stage failed.
    if %NOPAUSE%==0 pause
    exit /b 1
)

:: 阶段3: 后处理
echo.
echo [Stage 3/3] Post-Processing
echo ========================================
call "%SCRIPT_DIR%03_postprocess.bat"
if %errorlevel% neq 0 (
    echo Error: Post-processing stage failed.
    if %NOPAUSE%==0 pause
    exit /b 1
)

echo.
echo ========================================
echo Build completed successfully!
echo ========================================
echo.
echo Intermediate files location: %SCRIPT_DIR%..\Intermediate
echo Executable location: %SCRIPT_DIR%..\Binaries\Release\Launcher.exe
echo.

if %NOPAUSE%==0 pause 