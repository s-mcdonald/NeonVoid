@echo off

setlocal

:: Change to build directory
cd ..\build

::  Dr. Memory for Windows memleak issue
drmemory.exe ^
    -light ^
    -show_reachable ^
    -count_leaks ^
    -batch ^
    NeonVoid.exe

endlocal