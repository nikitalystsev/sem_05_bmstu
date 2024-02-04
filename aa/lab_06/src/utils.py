import numpy as np
import os
import random as rd
from brute_force_alg import brute_force_alg
from ant_alg import ant_alg


def gen_mtr_adj(size: int, rand_start: int, rand_end: int) -> np.ndarray:
    """
    Функция генерации случайной матрицы смежности
    """

    matrix = np.zeros((size, size), dtype=int)

    for i in range(size):
        for j in range(size):
            if i == j:
                num = 0
            else:
                num = rd.randint(rand_start, rand_end)
            matrix[i][j] = num
            matrix[j][i] = num

    return matrix


def gen_mtr_adj_in_file(filename: str, size: int, rand_start: int, rand_end: int) -> str:
    """
    Функция генерации случайной матрицы смежности в файл
    """

    mtr_adj: np.ndarray = gen_mtr_adj(size, rand_start, rand_end)

    with open("data/" + filename, "w") as file:
        for i in range(size):
            string = ""
            for j in range(size):
                string += str(mtr_adj[i][j])
                string += " "
            string += "\n"

            file.write(string)

    return "File %s was generated\n" % filename


def read_mtr_adj_from_file(filename: str) -> np.ndarray:
    """
    Функция для считывания матрицы смежности из файла
    """

    with open("data/" + filename, "r") as file:
        size = len(file.readline().split())
        file.seek(0)

        mtr_adj = np.zeros((size, size), dtype=int)

        for i, line in enumerate(file):
            for j, num in enumerate(line.split()):
                mtr_adj[i][j] = int(num)

    return mtr_adj


def get_list_data_files() -> list[str]:
    """
    Функция для получения списка доступных файлов для считывания
    """

    os.system("ls \data > files.txt")  # linux works

    with open("files.txt", "r") as f_files:
        files = f_files.read().split()

    print("\n\nДоступные файлы: ", len(files), " штук", )

    for i in range(len(files)):
        print("%d. %s" % (i + 1, files[i]))

    return files


def update_file():
    """
    Функция для обновления данных в файле
    """
    try:
        option = int(input("\nДобавить новый файл? (1 - да, 2 - нет): "))
        match option:
            case 1:
                file_name = input("\nВведите имя файла: ")
                size = int(input("\nВведите размер матрицы: "))
                rand_start = int(input("\nВведите начальное число рандома: "))
                rand_end = int(input("\nВведите конечное число рандома: "))
                print(gen_mtr_adj_in_file(file_name, size, rand_start, rand_end))
            case 2:
                files = get_list_data_files()
                num_file = int(input("\nВыберите файл: ")) - 1
                size = int(input("\nВведите размер матрицы: "))
                rand_start = int(input("\nВведите начальное число рандома: "))
                rand_end = int(input("\nВведите конечное число рандома: "))
                print(gen_mtr_adj_in_file(files[num_file], size, rand_start, rand_end))
            case _:
                raise ValueError("\nОшибка: Неверно выбран пункт")
        print("\n\nУспешно обновлен список файлов\n")
    except ValueError:
        print("\nОшибка: Неверно выбран пункт")


def print_mtr_adj() -> None:
    """
    Функция для вывода матрицы на экран
    """

    files = get_list_data_files()

    try:
        fileIndex = int(input("\nВыберите файл: ")) - 1
    except ValueError:
        print("Неверно выбран файл\n")
        return

    mtr_adj: np.ndarray = read_mtr_adj_from_file(files[fileIndex])

    for i in range(len(mtr_adj)):
        for j in range(len(mtr_adj[0])):
            print("%4d" % (mtr_adj[i][j]), end="")
        print()


def read_mtr_adj() -> np.ndarray:
    """
    Функция для считывания данных по варианту
    """

    mtr_adj: np.ndarray = read_mtr_adj_from_file("rus_cities.txt")

    return mtr_adj


def parse_brute_force_alg() -> None:
    """
    Функция для решения задачи коммивояжера полным перебором
    """

    mtr_adj: np.ndarray = read_mtr_adj()

    size = len(mtr_adj)

    result: tuple[list[int], int] = brute_force_alg(mtr_adj, size)

    print("\n\nМинимальная сумма пути = ", result[0],
          "\nПуть: ", result[1])


def read_coeff() -> tuple[float | int, float | int, float, int]:
    """
    Функция для ввода коэффициентов муравьиного алгоритма
    """

    try:
        alpha = float(input("\n\nВведите коэффициент alpha: "))
        beta = 1 - alpha
        evaporation = float(input("Введите коэффициент evaporation: "))
        cnt_days = int(input("Введите кол-во дней: "))
    except ValueError:
        print("Неправильный ввод!")
        alpha = 0
        beta = 1
        evaporation = 0.5
        cnt_days = 10

    return alpha, beta, evaporation, cnt_days


def parse_ant_alg() -> None:
    """
    Функция для решения задачи коммивояжера муравьиным алгоритмом
    """

    mtr_adj: np.ndarray = read_mtr_adj()

    size = len(mtr_adj)

    alpha, beta, evaporation, cnt_days = read_coeff()

    result: tuple[list[int], int] = ant_alg(mtr_adj, size, alpha, beta, evaporation, cnt_days)

    print("\n\nМинимальная сумма пути = ", result[0],
          "\nПуть: ", result[1])


def parse_all() -> None:
    """
    Функция для решения задачи коммивояжера обоими методами
    """

    mtr_adj = read_mtr_adj()

    size = len(mtr_adj)

    alpha, beta, evaporation, cnt_days = read_coeff()

    result: tuple[list[int], int] = brute_force_alg(mtr_adj, size)

    print("\n\nАлгоритм полного перебора \
            \n\tМинимальная длина пути = ", result[0],
          "\n\tПуть: ", result[1])

    result: tuple[list[int], int] = ant_alg(mtr_adj, size, alpha, beta, evaporation, cnt_days)

    print("\n\nМуравьиный алгоритм \
            \n\tМинимальная длина пути = ", result[0],
          "\n\tПуть: ", result[1])
