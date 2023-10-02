#!/bin/bash

file_name="$1"

if [[ "$file_name" == "data2_"*"_"*".txt" ]]; then
    echo "$file_name" > file_name.txt
    size=$(grep -oEm1 "[+-]?[0-9]+([.][0-9]+)?" file_name.txt | sed -n 2p)
    echo "$size"
elif [[ "$file_name" == "data3_"*"_"*".txt" ]]; then
    echo "$file_name" > file_name.txt
    size=$(grep -oEm1 "[+-]?[0-9]+([.][0-9]+)?" file_name.txt | sed -n 2p)
    echo "$size"
else
    echo "$file_name" > file_name.txt
    size=$(grep -oEm1 "[+-]?[0-9]+([.][0-9]+)?" file_name.txt | head -1)
    echo "$size"
fi

rm file_name.txt