@echo off
setlocal enabledelayedexpansion

REM Set Paths
set SCRIPT_DIR=%~dp0
set SCRIPT_DIR=%SCRIPT_DIR:~0,-1%
set GLM_DIR=%SCRIPT_DIR%\..\src\Runtime\vendor\glm
set GLFW_DIR=%SCRIPT_DIR%\..\src\Runtime\vendor\glfw3
set FREETYPE_DIR=%SCRIPT_DIR%\..\src\Runtime\vendor\freetype

echo.
echo.
echo.
echo.
echo Removing System Shared Libraries
echo ------------------------------------
echo.
echo.
echo.
echo Preparing GLM: OpenGL Mathematics
echo Link: https://github.com/g-truc/glm
echo.
echo.

cd /d "%GLM_DIR%"
cmake -DGLM_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=OFF -B build -S .
cmake --build build --config Release
cmake --install build --config Release

echo Preparing FreeType
echo Link: https://github.com/freetype/freetype
echo.
echo.

cd /d "%FREETYPE_DIR%"
if not exist build mkdir build
cmake -B build -S . -D CMAKE_BUILD_TYPE=Release
cmake --build build --config Release --target install

echo.
echo GLM and FreeType should now be installed.
echo.

pause
