#!/bin/bash

list_obj_files=$( (ls ../out/*.o))

words_sizes_for_time=("1" "2" "3" "4" "5" "6" "7" "8" "9" "10")
words_sizes_for_memory=("10" "20" "30" "40" "50" "60" "70" "80" "90" "100")

len_words_sizes_for_time=${#words_sizes_for_time[@]}
len_words_sizes_for_memory=${#words_sizes_for_memory[@]}

count_main_files_for_time=4
count_main_files_for_memory=4

if ! [ -d ./apps ]; then
    mkdir apps
fi

count=0
all_count=$((len_words_sizes_for_time * count_main_files_for_time))

echo "start compiling time!"

for size in "${words_sizes_for_time[@]}"; do
    g++ -std=c++20 -Wall -Werror -Wpedantic -DNMAX="${size}"\
    -Wextra -Wfloat-conversion -Wfloat-equal -O0 \
    $list_obj_files \
    -o ./apps/levNotRecur_"${size}".exe main01.cpp

    g++ -std=c++20 -Wall -Werror -Wpedantic -DNMAX="${size}"\
    -Wextra -Wfloat-conversion -Wfloat-equal -O0 \
    $list_obj_files \
    -o ./apps/damLevNotRecur_"${size}".exe main02.cpp

    g++ -std=c++20 -Wall -Werror -Wpedantic -DNMAX="${size}"\
    -Wextra -Wfloat-conversion -Wfloat-equal -O0 \
    $list_obj_files \
    -o ./apps/damLevRecur_"${size}".exe main03.cpp

    g++ -std=c++20 -Wall -Werror -Wpedantic -DNMAX="${size}"\
    -Wextra -Wfloat-conversion -Wfloat-equal -O0 \
    $list_obj_files \
    -o ./apps/damLevRecurCache_"${size}".exe main04.cpp

    count=$((count + count_main_files_for_time))
    echo -n -e "was compiling $count/$all_count files\r"
done

echo -e "\nfinish compiling time!"

count=0
all_count=$((len_words_sizes_for_memory * count_main_files_for_memory))

echo -e "\nstart compiling memory!"

for size in "${words_sizes_for_memory[@]}"; do
    g++ -std=c++20 -Wall -Werror -Wpedantic -DNMAX="${size}"\
    -Wextra -Wfloat-conversion -Wfloat-equal -O0 \
    $list_obj_files \
    -o ./apps/levNotRecurMem_"${size}".exe mainMem01.cpp

    g++ -std=c++20 -Wall -Werror -Wpedantic -DNMAX="${size}"\
    -Wextra -Wfloat-conversion -Wfloat-equal -O0 \
    $list_obj_files \
    -o ./apps/damLevNotRecurMem_"${size}".exe mainMem02.cpp

    g++ -std=c++20 -Wall -Werror -Wpedantic -DNMAX="${size}"\
    -Wextra -Wfloat-conversion -Wfloat-equal -O0 \
    $list_obj_files \
    -o ./apps/damLevRecurMem_"${size}".exe mainMem03.cpp

    g++ -std=c++20 -Wall -Werror -Wpedantic -DNMAX="${size}"\
    -Wextra -Wfloat-conversion -Wfloat-equal -O0 \
    $list_obj_files \
    -o ./apps/damLevRecurCacheMem_"${size}".exe mainMem04.cpp

    count=$((count + count_main_files_for_memory))
    echo -n -e "was compiling $count/$all_count files\r"
done
    
echo -e "\nfinish compiling memory!"
