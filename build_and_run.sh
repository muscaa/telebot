#!/bin/bash

source init.sh

source build.sh

# Run program if compilation was successful
if [ $? -eq 0 ]; then
    source run.sh $@
fi