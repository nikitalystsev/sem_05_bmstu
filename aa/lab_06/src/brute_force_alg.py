import numpy as np
import itertools as it


def get_curr_cost(curr_route: list[int], mtr_adj: np.ndarray) -> int:
    """
    Функция для нахождения стоимости маршрута curr_route
    :param curr_route: маршрут
    :param mtr_adj: матрица смежности для графа
    :return: стоимость маршрута curr_route
    """

    curr_cost = 0

    for i in range(len(curr_route) - 1):
        curr_cost += mtr_adj[curr_route[i]][curr_route[i + 1]]

    return curr_cost


def brute_force_alg(mtr_adj: np.ndarray, size: int) -> tuple[list[int], int]:
    """
    Функция для реализации алгоритма полного перебора
    :param mtr_adj: матрица смежности для графа
    :param size: количество городов (размер матрицы)
    :return: маршрут min_route и его стоимость min_cost
    """

    min_route = list()
    min_cost = float("inf")

    for perm in it.permutations(list(range(len(mtr_adj)))):
        curr_route = list(perm)
        # незамкнутый маршрут - не добавляем в конец curr_route начальную вершину

        curr_cost: int = get_curr_cost(curr_route, mtr_adj)

        if curr_cost < min_cost:
            min_route = curr_route
            min_cost = curr_cost

    return min_route, min_cost
