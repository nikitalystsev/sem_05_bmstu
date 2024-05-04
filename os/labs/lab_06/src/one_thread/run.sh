#!/bin/bash


# Получаем количество запусков из аргумента командной строки
num_runs=20

# Запускаем bakery_client определенное количество раз
for ((i=1; i<=$num_runs; i++)); do
    bash -c "./bakery_client 127.0.0.1"
    # Можно использовать любой другой терминал, например gnome-terminal, konsole и т. д., в зависимости от вашей системы
done