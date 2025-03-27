@echo off

:: Set the build configuration (Debug or Release)
set BUILD_TYPE=Debug

cmake -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% .

cmake --build . --config %BUILD_TYPE%

pause
