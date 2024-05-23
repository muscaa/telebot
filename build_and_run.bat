@echo off
setlocal EnableDelayedExpansion

call build.bat

rem Run program if compilation was successful
if %errorlevel% equ 0 (
    call run.bat %*
)
