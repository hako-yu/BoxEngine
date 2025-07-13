@echo off
setlocal enabledelayedexpansion

echo ========================================
echo BoxEngine Post-Processing Stage
echo ========================================

:: 设置构建目录
set BUILD_DIR=%~dp0..\Intermediate
set BINARIES_DIR=%~dp0..\Binaries

:: 检查构建目录是否存在
if not exist "%BUILD_DIR%" (
    echo Error: Build directory not found. Please run configuration and compilation stages first.
    pause
    exit /b 1
)

:: 后处理阶段 - 拷贝构建产物到Binaries目录
echo.
echo Post-processing: Copying build artifacts to Binaries directory...
cd /d "%BUILD_DIR%"

:: 创建Binaries/Release目录
if not exist "%BINARIES_DIR%\Release" mkdir "%BINARIES_DIR%\Release"

:: 查找并拷贝构建产物
echo Searching for build artifacts...

:: 查找可执行文件
for /r %%f in (Launcher.exe) do (
    if exist "%%f" (
        echo Found executable: %%f
        copy "%%f" "%BINARIES_DIR%\Release\" >nul
        if !errorlevel! equ 0 (
            echo Successfully copied Launcher.exe to Binaries\Release\
        ) else (
            echo Error: Failed to copy Launcher.exe
        )
    )
)

:: 查找库文件
for /r %%f in (Core.lib) do (
    if exist "%%f" (
        echo Found library: %%f
        copy "%%f" "%BINARIES_DIR%\Release\" >nul
        if !errorlevel! equ 0 (
            echo Successfully copied Core.lib to Binaries\Release\
        ) else (
            echo Error: Failed to copy Core.lib
        )
    )
)

echo Post-processing completed successfully. 