import utils
# from constants import CSV, LATEX
from time import process_time
import numpy as np
from brute_force_alg import brute_force_alg
from ant_alg import ant_alg
import matplotlib.pyplot as plt


def test_time():
    """
    Функция для проведения замеров времени
    """

    try:
        size_start = int(input("\n\nВведите начальный размер матрицы: "))
        size_end = int(input("Введите конечный размер матрицы: "))

        if size_start > size_end or size_start < 0 or size_end < 0:
            raise ValueError
    except ValueError:
        print("Неправильные размеры матрицы!")
        return

    time_brute_force_alg = []
    time_and_alg = []

    sizes = [i for i in range(size_start, size_end + 1)]

    count = 0

    print()

    n_reps = 10
    for size in sizes:
        count += 1
        end_bf = end_ant = 0
        for _ in range(n_reps):
            mtr_adj: np.ndarray = utils.gen_mtr_adj(size, 5, 10)

            start = process_time()
            brute_force_alg(mtr_adj, size)
            end_bf += (process_time() - start)

            start = process_time()
            ant_alg(mtr_adj, size, 0.5, 0.5, 0.5, 250)
            end_ant = (process_time() - start)

        time_brute_force_alg.append(end_bf / n_reps)
        time_and_alg.append(end_ant / n_reps)

        print("Progress: %3d%s" % ((count / len(sizes)) * 100, "%"))

    # Table
    print("\n %s | %s | %s" % ("Размер", "Время полного перебора", "Время муравьиного алгоритма"))
    print("-" * (8 + 1 + 24 + 1 + 29))

    for i in range(len(sizes)):
        print(" %6d | %22.6f | %27.6f" % (sizes[i], time_brute_force_alg[i], time_and_alg[i]))

    # For Latex
    with open("latex_table.txt", "w") as f_latex:
        for i in range(len(sizes)):
            f_latex.write("%4d & %10.6f & %10.6f \\\\ \\hline\n" % (sizes[i], time_brute_force_alg[i], time_and_alg[i]))

    # Graph
    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(sizes, time_brute_force_alg, marker='o', linestyle='--', label="Полный перебор")
    plot.plot(sizes, time_and_alg, marker='^', label="Муравьиный алгоритм")
    plt.yscale('log')  # Включаем логарифмическую шкалу

    plt.legend()
    plt.grid()
    plt.title("Временные характеристики")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Размер матрицы")

    # Включение отображения сетки
    plt.grid(True, linestyle='--', linewidth=0.5, alpha=0.7)
    # Сохранение графика в формате SVG
    plt.savefig("../report/inc/img/research1.svg", format='svg')

    plt.show()


def parametrization(_type: int = 1):
    """
    Функция для выполнения параметризации
    """
    sep = ", "  # по умолчанию csv файлы
    ender = ""

    alpha_arr = [num / 10 for num in range(1, 10)]
    eva_arr = [num / 10 for num in range(1, 9)]
    days_arr = [1, 3, 5, 10, 50, 100, 300, 500]

    size = 10

    mtr_adj1 = utils.read_mtr_adj_from_file("real.csv")
    mtr_adj2 = utils.read_mtr_adj_from_file("gen.csv")
    mtr_adj3 = utils.read_mtr_adj_from_file("gen.csv")

    optimal1: tuple[list[int], int] = brute_force_alg(mtr_adj1, size)
    optimal2: tuple[list[int], int] = brute_force_alg(mtr_adj2, size)
    optimal3: tuple[list[int], int] = brute_force_alg(mtr_adj3, size)

    with open("parametrization_class1.txt", "w") as file1, open("parametrization_class2.txt", "w") as file2, open(
            "parametrization_class3.txt", "w") as file3:
        count = 0
        count_all = len(alpha_arr) * len(eva_arr)

        print()

        for alpha in alpha_arr:
            beta = 1 - alpha
            for eva in eva_arr:
                count += 1

                for days in days_arr:
                    res1 = ant_alg(mtr_adj1, size, alpha, beta, eva, days)
                    res2 = ant_alg(mtr_adj2, size, alpha, beta, eva, days)
                    res3 = ant_alg(mtr_adj2, size, alpha, beta, eva, days)

                    match _type:
                        case 1:  # csv файлы
                            sep = ", "
                            ender = ""
                        case 2:  # latex файлы
                            sep = " & "
                            ender = " \\\\"
                        case _:
                            sep = " | "
                            ender = ""

                    str1 = "%4.1f%s%4.1f%s%4d%s%5d%s%5d%s\n" \
                           % (alpha, sep, eva, sep, days, sep, optimal1[1], sep, res1[0] - optimal1[1], ender)

                    str2 = "%4.1f%s%4.1f%s%4d%s%5d%s%5d%s\n" \
                           % (alpha, sep, eva, sep, days, sep, optimal2[1], sep, res2[0] - optimal2[1], ender)

                    str3 = "%4.1f%s%4.1f%s%4d%s%5d%s%5d%s\n" \
                           % (alpha, sep, eva, sep, days, sep, optimal3[1], sep, res3[0] - optimal3[1], ender)

                    file1.write(str1)
                    file2.write(str2)
                    file3.write(str3)

                print("Progress: %3d%s" % ((count / count_all) * 100, "%"))
