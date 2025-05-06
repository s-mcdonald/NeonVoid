@echo off
setlocal enabledelayedexpansion

REM Set Paths
set SCRIPT_DIR=%~dp0
set SCRIPT_DIR=%SCRIPT_DIR:~0,-1%
set GLM_DIR=%SCRIPT_DIR%\..\src\Runtime\vendor\glm
set GLFW_DIR=%SCRIPT_DIR%\..\src\Runtime\vendor\glfw
set FREETYPE_DIR=%SCRIPT_DIR%\..\src\Runtime\vendor\freetype

echo.
echo Preparing GLM: OpenGL Mathematics
echo Link: https://github.com/g-truc/glm
echo ------------------------------------
echo.
cd /d "%GLM_DIR%"
if not exist build mkdir build
@rem cmake -S . -B build -DGLM_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release
@rem cmake --build build --config Release
@rem cmake --build build --config Release --target install

cmake -S . -B build ^
  -DGLM_BUILD_TESTS=OFF ^
  -DBUILD_SHARED_LIBS=ON ^
  -DCMAKE_BUILD_TYPE=Release ^
  -DCMAKE_INSTALL_PREFIX="%GLM_DIR%\build"

cmake --build build --config Release --target install





echo.
echo Preparing FreeType
echo Link: https://github.com/freetype/freetype
echo ------------------------------------
echo.
cd /d "%FREETYPE_DIR%"
if not exist build mkdir build
@rem cmake -B build -S . -D CMAKE_BUILD_TYPE=Release
cmake -B build -D CMAKE_INSTALL_PREFIX="%FREETYPE_DIR%/build" -D BUILD_SHARED_LIBS=true -D CMAKE_BUILD_TYPE=Release "%FREETYPE_DIR%"
cmake --build build --target install


echo.
echo Preparing GLFW
echo Link: https://github.com/glfw/glfw
echo ------------------------------------
echo.
cd /d "%GLFW_DIR%"
cmake -S . -B build -D GLFW_BUILD_EXAMPLES=OFF -D GLFW_BUILD_TESTS=OFF -D GLFW_BUILD_DOCS=OFF -D BUILD_SHARED_LIBS=ON -D CMAKE_INSTALL_PREFIX="%GLFW_DIR%/build/lib"
@rem cmake --build build --target all
cmake --build build
cmake --build build --target install


echo.
echo ====================================
echo.
echo GLFW, GLM and FreeType should now be installed.
echo.

pause
