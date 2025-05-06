@echo off

:: Set the build configuration (Debug or Release)
set BUILD_TYPE=Debug

cmake -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ..

@REM cmake --build .. --config %BUILD_TYPE%
cmake --build .

pause
