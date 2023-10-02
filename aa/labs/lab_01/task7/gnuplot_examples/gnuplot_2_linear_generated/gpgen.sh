#!/bin/bash

echo "#!/usr/bin/gnuplot -persist"
echo "reset"
echo "NO_ANIMATION = 1"
#set terminal svg size 1920, 1080
#set output 'myfile.svg'
#set size ratio 0.61803
#set size ratio 0.5625
echo 'set xlabel "Количество элементов, шт"'
echo 'set ylabel "Время, с"'
echo "set grid"

listt=$(ls ./preproc_data/)

echo "plot sin(x)"

for li in $listt; do
	echo "replot './preproc_data/$li' with linespoints"
done
