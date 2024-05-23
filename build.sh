#!/bin/bash

source init.sh

# Create build folder if it doesn't exist
mkdir -p build/

# Get all C++ files in src folder
cpp_files=$(find src/ -name '*.cpp')

# Compile all C++ files
g++ -std=c++17 -Wall -o build/program $cpp_files