#!/bin/bash

build() 
{
    local params_name="$1[@]"
    local comp_files_name="$2[@]"
    local params=("${!params_name}")
    local comp_files=("${!comp_files_name}")

    local len_params=${#params[@]}
    local len_comp_files=${#comp_files[@]}

    local count=0
    local all_count=$((len_params * len_comp_files))

    echo -e "\nstart compiling ${3}!"

    for param in "${params[@]}"; do
        for comp_file in "${comp_files[@]}"; do
            g++ -std=c++20 -Wall -Werror -Wpedantic -DNMAX="${param}"\
            -Wextra -Wfloat-conversion -Wfloat-equal -O0 \
            $list_obj_files \
            -o ./apps/"${comp_file}"_"${param}".exe "${comp_file}.cpp"

            count=$((count + 1))
            echo -n -e "was compiling $count/$all_count files\r"
        done   
    done

    echo -e "\nfinish compiling ${3}!"
}

. app_params.sh

list_obj_files=$( (ls ../out/*.o))

if ! [ -d ./apps ]; then
    mkdir apps
fi

build num_str1 comp_files_time1 "time_100-1000_str"
