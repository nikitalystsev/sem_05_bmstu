#!/bin/bash

cd postproc_scripts || exit

# ./create_linear_time_rand.gpi
# ./create_linear_time_asc.gpi
# ./create_linear_time_desc.gpi
# ./create_linear_time_same.gpi
./create_linear_mem.gpi

cd ..
