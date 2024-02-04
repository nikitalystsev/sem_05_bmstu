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

# def parametrization(type=CSV):
#     alpha_arr = [num / 10 for num in range(1, 10)]
#     k_eva_arr = [num / 10 for num in range(1, 9)]
#     days_arr = [1, 3, 5, 10, 50, 100, 300, 500]
#
#     size = 8
#
#     matrix1 = readFileMatrix("real.csv")
#     matrix2 = readFileMatrix("gen.csv")
#
#     optimal1 = fullCombinationAlg(matrix1, size)
#     optimal2 = fullCombinationAlg(matrix2, size)
#
#     file1 = open("parametrization_class1.txt", "w")
#     file2 = open("parametrization_class2.txt", "w")
#
#     count = 0
#     count_all = len(alpha_arr) * len(k_eva_arr)
#
#     print()
#
#     for alpha in alpha_arr:
#         beta = 1 - alpha
#         for k_eva in k_eva_arr:
#             count += 1
#
#             for days in days_arr:
#                 res1 = antAlgorithm(matrix1, size, alpha, beta, k_eva, days)
#                 res2 = antAlgorithm(matrix2, size, alpha, beta, k_eva, days)
#
#                 if (type == LATEX):
#                     sep = " & "
#                     ender = " \\\\"
#                 elif (type == CSV):
#                     sep = ", "
#                     ender = ""
#                 else:
#                     sep = " | "
#                     ender = ""
#
#                 str1 = "%4.1f%s%4.1f%s%4d%s%5d%s%5d%s\n" \
#                        % (alpha, sep, k_eva, sep, days, sep, optimal1[0], sep, res1[0] - optimal1[0], ender)
#
#                 str2 = "%4.1f%s%4.1f%s%4d%s%5d%s%5d%s\n" \
#                        % (alpha, sep, k_eva, sep, days, sep, optimal2[0], sep, res2[0] - optimal2[0], ender)
#
#                 file1.write(str1)
#                 file2.write(str2)
#
#             print("Progress: %3d%s" % ((count / count_all) * 100, "%"))
#
#     file1.close()
#     file2.close()
