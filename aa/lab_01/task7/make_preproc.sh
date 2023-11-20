#!/bin/bash

words_sizes_for_time=("1" "2" "3" "4" "5" "6" "7" "8" "9" "10")
words_sizes_for_memory=("10" "20" "30" "40" "50" "60" "70" "80" "90" "100")

len_words_sizes_for_time=${#words_sizes_for_time[@]}
len_words_sizes_for_memory=${#words_sizes_for_memory[@]}

count_main_files_for_time=4
count_main_files_for_memory=4

count=5 # сколько раз запускается прога (каждая)

if ! [ -d ./data ]; then
    mkdir data
fi

################################################################################################################

# сборка основного датасета

# компилирую
bash build_apps.sh

counter=0 # счетчик
all_count=$((len_words_sizes_for_time * count * count_main_files_for_time)) 

echo -e "\nstart collecting data time!"

for size in "${words_sizes_for_time[@]}"; do
    for c in $(seq "$count"); do
        # запускаю тестирование вот тут,
        # count отвечает за количество строчек в файле ./data/data"${number}"_"${array_size}".txt
        ./apps/levNotRecur_"${size}".exe >> ./data/levNotRecur_"${size}".txt

        ./apps/damLevNotRecur_"${size}".exe >> ./data/damLevNotRecur_"${size}".txt
        
        ./apps/damLevRecur_"${size}".exe >> ./data/damLevRecur_"${size}".txt

        ./apps/damLevRecurCache_"${size}".exe >> ./data/damLevRecurCache_"${size}".txt

        counter=$((counter + count_main_files_for_time))
        echo -n -e "was collecting $counter/$all_count;  $c/$count, size = $size \r"
    done
done
echo  -e "\nfinish collecting data time!"

counter=0 # счетчик
all_count=$((len_words_sizes_for_memory * count * count_main_files_for_memory))

echo -e "\nstart collecting data memory!"

for size in "${words_sizes_for_memory[@]}"; do
    for c in $(seq "$count"); do
        # запускаю тестирование вот тут,
        # count отвечает за количество строчек в файле ./data/data"${number}"_"${array_size}".txt
        ./apps/levNotRecurMem_"${size}".exe >> ./data/levNotRecurMem_"${size}".txt

        ./apps/damLevNotRecurMem_"${size}".exe >> ./data/damLevNotRecurMem_"${size}".txt
        
        ./apps/damLevRecurMem_"${size}".exe >> ./data/damLevRecurMem_"${size}".txt

        ./apps/damLevRecurCacheMem_"${size}".exe >> ./data/damLevRecurCacheMem_"${size}".txt

        counter=$((counter + count_main_files_for_memory))
        echo -n -e "was collecting $counter/$all_count;  $c/$count, size = $size \r"
    done
done

echo  -e "\nfinish collecting data memory!"

#################################################################################################################

# первичный анализ и подготовка данных для построения первого графика

ls ./data > ls_data.txt
files=$(grep -v "clean.sh" ls_data.txt)
rm ls_data.txt


if ! [ -d ./postproc_data ]; then
    mkdir postproc_data
fi

if ! [ -d ./postproc_data/grap1 ]; then
    mkdir postproc_data/grap1
fi

counter=0
all_count=$(( len_words_sizes_for_time  * count_main_files_for_time))

echo -e "\nstart get info for graph1!"

for size in "${words_sizes_for_time[@]}"; do
    for file in $files; do

        cd preproc_scripts/ || exit
        bash build_c_scripts.sh
        cd ../

        if [ "${file}" == "levNotRecur_""${size}"".txt" ]; then
            ar_time=$(preproc_scripts/ar_mean.exe < ./data/"${file}")
            echo "${size} ${ar_time}" >> ./postproc_data/grap1/levNotRecur.txt
            counter=$((counter + 1))
        fi

        if [ "${file}" == "damLevNotRecur_""${size}"".txt" ]; then
            ar_time=$(preproc_scripts/ar_mean.exe < ./data/"${file}")
            echo "${size} ${ar_time}" >> ./postproc_data/grap1/damLevNotRecur.txt
            counter=$((counter + 1))
        fi

        if [ "${file}" == "damLevRecur_""${size}"".txt" ]; then
            ar_time=$(preproc_scripts/ar_mean.exe < ./data/"${file}")
            echo "${size} ${ar_time}" >> ./postproc_data/grap1/damLevRecur.txt
            counter=$((counter + 1))
        fi

        if [ "${file}" == "damLevRecurCache_""${size}"".txt" ]; then
            ar_time=$(preproc_scripts/ar_mean.exe < ./data/"${file}")
            echo "${size} ${ar_time}" >> ./postproc_data/grap1/damLevRecurCache.txt
            counter=$((counter + 1))
        fi

        echo -n -e "$counter/$all_count records were received\r"
    done
done

echo  -e "\nfinish get info for graph1!"

#################################################################################################################

# первичный анализ и подготовка данных для построения второго графика

if ! [ -d ./postproc_data/grap2 ]; then
    mkdir postproc_data/grap2
fi

counter=0
all_count=$(( len_words_sizes_for_memory  * count_main_files_for_memory))

echo -e "\nstart get info for graph2!"

for size in "${words_sizes_for_memory[@]}"; do
    for file in $files; do

        cd preproc_scripts/ || exit
        bash build_c_scripts.sh  
        cd ../

        if [ "${file}" == "levNotRecurMem_""${size}"".txt" ]; then
            ar_time=$(preproc_scripts/ar_mean.exe < ./data/"${file}")
            echo "${size} ${ar_time}" >> ./postproc_data/grap2/levNotRecurMem.txt
            counter=$((counter + 1))
        fi

        if [ "${file}" == "damLevNotRecurMem_""${size}"".txt" ]; then
            ar_time=$(preproc_scripts/ar_mean.exe < ./data/"${file}")
            echo "${size} ${ar_time}" >> ./postproc_data/grap2/damLevNotRecurMem.txt
            counter=$((counter + 1))
        fi

        if [ "${file}" == "damLevRecurMem_""${size}"".txt" ]; then
            ar_time=$(preproc_scripts/ar_mean.exe < ./data/"${file}")
            echo "${size} ${ar_time}" >> ./postproc_data/grap2/damLevRecurMem.txt
            counter=$((counter + 1))
        fi

        if [ "${file}" == "damLevRecurCacheMem_""${size}"".txt" ]; then
            ar_time=$(preproc_scripts/ar_mean.exe < ./data/"${file}")
            echo "${size} ${ar_time}" >> ./postproc_data/grap2/damLevRecurCacheMem.txt
            counter=$((counter + 1))
        fi

        echo -n -e "$counter/$all_count records were received\r"
    done
done

echo  -e "\nfinish get info for graph2!"