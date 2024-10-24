#!/bin/bash

get_data()
{
    local params_name="$1[@]"
    local comp_files_name="$2[@]"
    local params=("${!params_name}")
    local comp_files=("${!comp_files_name}")

    local len_params=${#params[@]}
    local len_comp_files=${#comp_files[@]}

    local count="${3}" # сколько раз запускается каждая прога

    local counter=0
    local all_count=$((len_params * count * len_comp_files))
    
    echo -e "\nstart collecting data ${4}!"

    for param in "${params[@]}"; do
        for comp_file in "${comp_files[@]}"; do
            for c in $(seq "$count"); do
                ./apps/"${comp_file}"_"${param}".exe >> ./data/"${comp_file}"_"${param}".txt

                counter=$((counter + 1))
                echo -n -e "was collecting $counter/$all_count;  $c/$count, size = ${param} \r"
            done
        done 
    done

    echo  -e "\nfinish collecting data ${4}!"
}

analysis_data()
{
    local params_name="$1[@]"
    local comp_files_name="$2[@]"
    local params=("${!params_name}")
    local comp_files=("${!comp_files_name}")

    local len_params=${#params[@]}
    local len_comp_files=${#comp_files[@]}

    local counter=0
    local all_count=$((len_params * len_comp_files))
    
    echo -e "\nstart get info for ${3}!"

    for param in "${params[@]}"; do
        for comp_file in "${comp_files[@]}"; do
            ar_time=$(preproc_scripts/ar_mean.exe < ./data/"${comp_file}"_"${param}".txt)
            echo "${param} ${ar_time}" >> ./postproc_data/"${3}"/"${comp_file}".txt

            counter=$((counter + 1))
            echo -n -e "$counter/$all_count records were received\r"
        done 
    done

    echo  -e "\nfinish get info for ${3}!"
}

# Импортируем общие данные
. app_params.sh

# компилирую
bash build_apps.sh

cd preproc_scripts/ || exit
bash build_scripts.sh
cd ../

if ! [ -d ./data ]; then
    mkdir data
fi

############################################################################

# сборка основного датасета

# get_data num_str1 comp_files_time1 10 "time_10-100_str"
get_data cnt_threads2 comp_files_time2 10 "time_100_str"

# ##########################################################################

# # первичный анализ и подготовка данных для построения первого графика

if ! [ -d ./postproc_data ]; then
    mkdir postproc_data
fi

if ! [ -d ./postproc_data/graph1 ]; then
    mkdir postproc_data/graph1
fi

# analysis_data num_str1 comp_files_time1 "graph1"

# # #########################################################################

# # первичный анализ и подготовка данных для построения второго графика

if ! [ -d ./postproc_data/graph2 ]; then
    mkdir postproc_data/graph2
fi

analysis_data cnt_threads2 comp_files_time2 "graph2"

# ########################################################################

# # первичный анализ и подготовка данных для построения третьего графика

if ! [ -d ./postproc_data/graph3 ]; then
    mkdir postproc_data/graph3
fi

# analysis_data sizes_mem comp_files_mem "graph3"
