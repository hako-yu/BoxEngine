@echo off
setlocal enabledelayedexpansion

echo ========================================
echo BoxEngine Windows Runner Script
echo ========================================



:: 检查参数
set "HELP_ONLY=0"

:parse_args
if "%1"=="" goto :end_parse
if "%1"=="--help" set "HELP_ONLY=1"
shift
goto :parse_args
:end_parse

:: 显示帮助信息
if %HELP_ONLY%==1 (
    echo.
    echo Usage: run.bat [options]
    echo.
    echo Options:
    echo   --help          Show this help message
    echo.
    echo This script runs the built BoxEngine project.
    echo Make sure the project is built before running this script.
    echo.
    pause
    exit /b 0
)

:: 设置路径
set "PROJECT_ROOT=%~dp0"
set "BUILD_DIR=%PROJECT_ROOT%Engine\Binaries"
set "EXECUTABLE=%BUILD_DIR%\Release\Launcher.exe"

:: 检查可执行文件是否存在
if not exist "%EXECUTABLE%" (
    echo Error: Executable not found at %EXECUTABLE%
    echo Please build the project first using Engine\Build\build.bat
    echo.
    echo Expected location: %EXECUTABLE%
    echo.
    pause
    exit /b 1
)

:: 运行项目
echo Running BoxEngine...
echo.

:: 切换到可执行文件目录
cd /d "%BUILD_DIR%\Release"

:: 运行程序
echo Starting Launcher.exe...
echo.

"%EXECUTABLE%"

:: 检查程序退出状态
if %errorlevel% neq 0 (
    echo.
    echo Program exited with error code: %errorlevel%
) else (
    echo.
    echo Program completed successfully.
)

echo.
echo Press any key to exit...
pause >nul 