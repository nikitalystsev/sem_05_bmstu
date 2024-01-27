#!/bin/bash

cd postproc_scripts || exit

./create_linear_time1.gpi
./create_linear_time2.gpi
# ./create_linear_mem.gpi

cd ..
