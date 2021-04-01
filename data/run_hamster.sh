#!/bin/bash

wmctrl -l | awk '{$1=$2=$3="";print}' | grep "🐹 Hamster"

if [ $? -eq 0 ]; then
    wmctrl -a "🐹 Hamster"
    exit 1
else
    ~/repos/hamster/build/src/bin/hamster
    exit 0
fi
