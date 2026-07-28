#!/bin/sh

if [ -z "$1" ]
then
    echo 'Please provide the filename of the implementation (without the extension or directory).'
else
    mkdir -p bin
    mkdir -p obj
    gcc -Wall -Wextra -Wno-unused-function -Wno-unused-parameter -Wno-pointer-sign -O3 base.c -c -o obj/base.o
    gcc -Wall -Wextra -Wno-unused-function -Wno-unused-parameter -Wno-pointer-sign -O3 main.c -c -o obj/main.o
    gcc -Wall -Wextra -Wno-unused-function -Wno-unused-parameter -Wno-pointer-sign -O3 "implementations/$1.c" -c -o "obj/$1.o"
    gcc obj/main.o obj/base.o "obj/$1.o" -o "bin/$1"
fi
