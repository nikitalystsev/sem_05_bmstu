#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -g3  -c main.c
gcc -o app.exe main.o -lm
