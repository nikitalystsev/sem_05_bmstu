# import matplotlib.pyplot as plt
# import numpy as np
#
# # Данные для первого алгоритма
# nodes = [2 ** i for i in range(7, 12)]
# bst_result = [1 for _ in range(5)]
#
# # Данные для второго алгоритма
# awl_result = [1 for _ in range(5)]
#
# # Ширина столбцов
# bar_width = 0.35
#
# # Создание массива с позициями для каждого столбца
# bar_positions_algorithm1 = np.arange(len(nodes))
# bar_positions_algorithm2 = bar_positions_algorithm1 + bar_width
#
# # Создание объекта фигуры с установкой размеров
# plt.figure(figsize=(8, 6))
#
# # Создание столбчатой диаграммы
# plt.bar(bar_positions_algorithm1, bst_result, width=bar_width, label='ДДП', hatch='//')
# plt.bar(bar_positions_algorithm2, awl_result, width=bar_width, label='АВЛ-дерево', hatch='\\')
#
# # Добавление заголовка и подписей осей
# plt.xlabel('Число узлов в дереве')
# plt.ylabel('Количество сравнений')
#
# # Добавление легенды с управлением положением
# plt.legend()
#
# # Установка меток на оси X
# plt.xticks(bar_positions_algorithm1 + bar_width / 2, nodes)
#
# # Сохранение графика в файл
# plt.savefig("../report/inc/img/research1.svg", format='svg')
#
# # Отображение диаграммы
# plt.show()

"""
когда искомый элемент в листе на максимальной высоте дерева
"""

import matplotlib.pyplot as plt
import numpy as np
nodes = [2 ** i for i in range(7, 12)]
# Данные для первого алгоритма
#           1658 928 501 77  1430
bst_result = [14, 14, 20, 22, 24]

# Данные для второго алгоритма
#          1658 928 872 901 1478
awl_result = [8, 9, 11, 11, 11]

# Ширина столбцов
bar_width = 0.35

# Создание массива с позициями для каждого столбца
bar_positions_algorithm1 = np.arange(len(nodes))
bar_positions_algorithm2 = bar_positions_algorithm1 + bar_width

# Создание столбчатой диаграммы
plt.bar(bar_positions_algorithm1, bst_result, width=bar_width, label='ДДП', hatch='//')
plt.bar(bar_positions_algorithm2, awl_result, width=bar_width, label='АВЛ-дерево', hatch='\\')

# Добавление заголовка и подписей осей
plt.xlabel('Число узлов в дереве')
plt.ylabel('Количество сравнений')

# Добавление легенды с управлением положением
plt.legend()

# Установка меток на оси X
plt.xticks(bar_positions_algorithm1 + bar_width / 2, nodes)

# Добавление значений над каждым столбцом
for x, value in zip(bar_positions_algorithm1, bst_result):
    plt.text(x, value + 0.05, str(value), ha='center', va='bottom')

for x, value in zip(bar_positions_algorithm2, awl_result):
    plt.text(x, value + 0.05, str(value), ha='center', va='bottom')


# Сохранение графика в файл
plt.savefig("../report/inc/img/research2.svg", format='svg')

# Отображение диаграммы
plt.show()

# # когда не нашли
# import matplotlib.pyplot as plt
# import numpy as np
#
# # Данные для первого алгоритма
# nodes = [2 ** i for i in range(7, 12)]
#              # 13  13 13 33  13
# bst_result = [5, 9, 8, 16, 12]
#
# # Данные для второго алгоритма
# #              13  13 13  33  13
# awl_result = [7, 9, 10, 12, 11]
#
# # Ширина столбцов
# bar_width = 0.35
#
# # Создание массива с позициями для каждого столбца
# bar_positions_algorithm1 = np.arange(len(nodes))
# bar_positions_algorithm2 = bar_positions_algorithm1 + bar_width
#
# # Создание столбчатой диаграммы
# plt.bar(bar_positions_algorithm1, bst_result, width=bar_width, label='ДДП', hatch='//')
# plt.bar(bar_positions_algorithm2, awl_result, width=bar_width, label='АВЛ-дерево', hatch='\\')
#
# # Добавление заголовка и подписей осей
# plt.xlabel('Число узлов в дереве')
# plt.ylabel('Количество сравнений')
#
# # Добавление легенды с управлением положением
# plt.legend()
#
# # Установка меток на оси X
# plt.xticks(bar_positions_algorithm1 + bar_width / 2, nodes)
#
# # Добавление значений над каждым столбцом
# for x, value in zip(bar_positions_algorithm1, bst_result):
#     plt.text(x, value + 0.05, str(value), ha='center', va='bottom')
#
# for x, value in zip(bar_positions_algorithm2, awl_result):
#     plt.text(x, value + 0.05, str(value), ha='center', va='bottom')
#
#
# # Сохранение графика в файл
# plt.savefig("../report/inc/img/research3.svg", format='svg')
#
# # Отображение диаграммы
# plt.show()
#
