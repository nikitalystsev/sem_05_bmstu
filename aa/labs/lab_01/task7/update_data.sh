#!/bin/bash

cprog="main.c"
number=""
array_size="1000"
opt="O0"
count=10

if ! [ -d ./data ]; then
    mkdir data
fi

if [ "$1" == "main.c" ]; then
    cprog=$1
    number=""
elif [ "$1" == "main2.c" ]; then
    cprog=$1
    number="2"
elif [ "$1" == "main3.c" ]; then
    cprog=$1
    number="3"
fi

if [ -n  "$2" ]; then
    array_size="$2"
fi

if [ -n "$3" ]; then
    opt="$3"
fi

if [ -n "$4" ]; then
    count="$4"
fi

#################################################################################################################

# добавление данных в датасет

echo "start update data!"

for c in $(seq "$count"); do
    echo -n -e "$c/$count $opt $array_size for $cprog \r"
    # если нет исполняемого файла, то я его компилирую, т. е. создаю, и запускаю тестирование
    if [ ! -e ./apps/app"${number}"_"${array_size}"_"${opt}".exe ]; then
        gcc -std=c99 -Wall -Werror -Wpedantic -DNMAX="${array_size}"\
        -Wextra -Wfloat-conversion -Wfloat-equal -"${opt}" \
        -Wvla -o ./apps/app"${number}"_"${array_size}"_"${opt}".exe "$cprog"
    fi
    # запускаю тестирование вот тут, count отвечает за количество строчек в файле ./data/data"${number}"_"${array_size}"_"${opt}".txt
    ./apps/app"${number}"_"${array_size}"_"${opt}".exe >> ./data/data"${number}"_"${array_size}"_"${opt}".txt
done

#################################################################################################################

# добавление данных из полученного выше файла датасета к необходимым графикам

file="data""${number}""_""${array_size}""_""${opt}"".txt"

cd preproc_scripts/ || exit
bash build_c_scripts.sh "one"
cd ../

ar_time=$(preproc_scripts/ar_mean.exe < ./data/"${file}")

sizes=()
while IFS=" " read -r line; do sizes+=("$line"); done < <(grep -oE "^[0-9]+" ./postproc_data/grap1/"data""${number}""_""${opt}"".txt")

result_size=""
for size in "${sizes[@]}"; do
    if [ "${size}" -ge "${array_size}" ]; then
        result_size="${size}"
        break
    fi
done
if [ "${result_size}" != "" ]; then
    number_str="$(grep -ne "^${result_size}" ./postproc_data/grap1/data"${number}"_"${opt}".txt | cut -d : -f 1 | head -1)"
    sed "${number_str}i\\${array_size} ${ar_time}" ./postproc_data/grap1/data"${number}"_"${opt}".txt > ./postproc_data/grap1/bbb.txt
    rm ./postproc_data/grap1/data"${number}"_"${opt}".txt
    mv ./postproc_data/grap1/bbb.txt ./postproc_data/grap1/data"${number}"_"${opt}".txt
else
    echo "${array_size} ${ar_time}" >> ./postproc_data/grap1/data"${number}"_"${opt}".txt
fi

echo -e "\nfinish update data!"

#################################################################################################################
