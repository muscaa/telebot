@echo off
setlocal EnableDelayedExpansion

if exist build\program.exe (
    cd build
    program %*
    set "exit=!errorlevel!"

    echo.
    echo.
    echo.
    echo Program exited with code !exit!.
    echo.
)
