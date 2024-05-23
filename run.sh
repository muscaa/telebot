#!/bin/bash

source init.sh

if [ -f ./build/program ]; then
    cd build/
    ./program $@
    exit=$?

    echo
    echo
    echo
    echo "Program exited with code $exit."
    echo
fi