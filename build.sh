#!/bin/sh

if [ -z "$1" ]
then
    echo 'Please provide the filename of the implementation (without the extension or directory).'
else
    mkdir -p bin
    gcc -Wall -Wextra -Wno-unused-function -Wno-unused-parameter -Wno-pointer-sign main.c base.c "implementations/$1.c" -o "bin/$1"
fi
