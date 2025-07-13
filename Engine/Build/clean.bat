@echo off
setlocal enabledelayedexpansion

echo ========================================
echo BoxEngine Clean Script for Windows
echo ========================================

:: 检查参数
set "NOPAUSE=0"
if "%1"=="nopause" set "NOPAUSE=1"

:: 设置目录
set INTERMEDIATE_DIR=%~dp0..\Intermediate
set BINARIES_DIR=%~dp0..\Binaries

echo Cleaning build artifacts...

:: 清理中间产物
if exist "%INTERMEDIATE_DIR%" (
    echo Removing Intermediate directory...
    rmdir /s /q "%INTERMEDIATE_DIR%"
    if %errorlevel% equ 0 (
        echo Successfully removed Intermediate directory.
    ) else (
        echo Warning: Failed to remove Intermediate directory.
    )
) else (
    echo Intermediate directory not found.
)

:: 清理最终产物
if exist "%BINARIES_DIR%" (
    echo Removing Binaries directory...
    rmdir /s /q "%BINARIES_DIR%"
    if %errorlevel% equ 0 (
        echo Successfully removed Binaries directory.
    ) else (
        echo Warning: Failed to remove Binaries directory.
    )
) else (
    echo Binaries directory not found.
)

echo.
echo Clean completed successfully!
echo.

if %NOPAUSE%==0 pause 