#!/bin/bash

cd postproc_data || exit

./create_linear.gpi
./create_linear_mem.gpi

cd ..
