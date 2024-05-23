@echo off
setlocal EnableDelayedExpansion

rem Create build folder if it doesn't exist
if not exist build mkdir build

rem Get all C++ files in src folder
set "cpp_files="
for /r src %%f in (*.cpp) do (
    set "cpp_files=!cpp_files! "%%f""
)

rem Compile all C++ files
g++ -std=c++17 -Wall -o build\program !cpp_files!