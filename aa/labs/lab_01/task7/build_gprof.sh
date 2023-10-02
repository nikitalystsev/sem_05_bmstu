#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -g3 -pg -o app.exe main.c -lm
