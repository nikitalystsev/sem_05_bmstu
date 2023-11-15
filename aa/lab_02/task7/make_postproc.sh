#!/bin/bash

cd postproc_scripts || exit

./create_linear_time.gpi
./create_linear_mem.gpi

cd ..
