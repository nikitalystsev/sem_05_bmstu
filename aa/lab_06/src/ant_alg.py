import numpy as np
from random import random

START_PHEROMONE = 1
MIN_PHEROMONE = START_PHEROMONE / 10


def calc_Q(mtr_adj: np.ndarray, size: int) -> float:
    """
    Функция для вычисления значения пар-ра Q - квота (некоторая константа)
    феромона 1-го муравья на день
    :param mtr_adj: матрица смежности для графа
    :param size: количество городов (размер матрицы)
    :return: значения пар-ра Q
    """

    _sum = 0
    count = 0

    for i in range(size):
        for j in range(size):
            if i != j:
                _sum += mtr_adj[i][j]
                count += 1

    return _sum / count


def init_mtr_phero(size: int) -> np.ndarray:
    """
    Функция для создания матрицы феромонов и инициализации ее некоторым
    начальным значением (здесь 1)
    :param size: размер матрицы феромонов (соизмерима с матрицей смежности графа)
    :return: матрица феромонов
    """

    return np.ones((size, size))


def init_mtr_visib(mtr_adj: np.ndarray, size: int) -> np.ndarray:
    """
    Функция для создания матрицы видимости
    :param mtr_adj: матрица смежности для графа
    :param size: размер матрицы видимости (соизмерима с матрицей смежности графа)
    :return: матрица видимости
    """

    mtr_visib = [[(1.0 / mtr_adj[i][j] if i != j else 0) for j in range(size)] for i in range(size)]
    mtr_visib = np.array(mtr_visib)

    return mtr_visib


def get_prob_numerator(
        city_from: int,
        city_to: int,
        mtr_phero: np.ndarray,
        mtr_visib: np.ndarray,
        alpha: float,
        beta: float
) -> float:
    """
    Функция для вычисления числителя в формуле для подсчета вероятности
    выбора того или иного города
    :param city_from: город, в котором находится муравей k
    :param city_to: город, в который может перейти муравей k
    :param mtr_phero: матрица феромонов
    :param mtr_visib: матрица видимости
    :param alpha: пар-р влияния видимости пути
    :param beta: пар-р влияния феромона
    :return: числителя в формуле для подсчета вероятности
    """

    P = (mtr_phero[city_from][city_to] ** alpha) * (mtr_visib[city_from][city_to] ** beta)

    return P


def get_probabilities(
        size: int,
        tabu_k: list,
        mtr_phero: np.ndarray,
        mtr_visib: np.ndarray,
        alpha: float,
        beta: float
) -> np.ndarray:
    """
    Функция для подсчета вероятностей того, что муравей k пойдет
    в тот или иной город
    :param size: количество городов (размер матрицы)
    :param tabu_k: ранее посещенные муравьем k города
    :param mtr_phero: матрица феромонов
    :param mtr_visib: матрица видимости
    :param alpha: пар-р влияния видимости пути
    :param beta: пар-р влияния феромона
    :return: список вероятностей
    """

    probabilities = np.zeros(size)

    for city in range(size):
        if city not in tabu_k:
            curr_city = tabu_k[-1]

            probabilities[city] = get_prob_numerator(curr_city, city, mtr_phero, mtr_visib, alpha, beta)

    denominator = sum(probabilities)

    probabilities /= denominator

    return probabilities


def get_next_city(
        tabu_k: list[int],
        mtr_phero: np.ndarray,
        mtr_visib: np.ndarray,
        size: int,
        alpha: float,
        beta: float
) -> int:
    """
    Функция для определения следующего города, в который пойдет k-й муравей
    :param tabu_k: ранее посещенные муравьем k города
    :param mtr_phero: матрица феромонов
    :param mtr_visib: матрица видимости
    :param size: количество городов (размер матрицы)
    :param alpha: пар-р влияния видимости пути
    :param beta: пар-р влияния феромона
    :return: выбранный город
    """

    probabilities: np.ndarray = get_probabilities(size, tabu_k, mtr_phero, mtr_visib, alpha, beta)

    choice: float = random()

    probSum = probabilities[0]
    next_city = 0

    while choice > probSum and next_city < size - 1:
        next_city += 1
        probSum += probabilities[next_city]

    return next_city


def get_ant_route(
        ant_k: dict,
        mtr_adj: np.ndarray,
        mtr_phero: np.ndarray,
        mtr_visib: np.ndarray,
        size: int,
        alpha: float,
        beta: float
) -> dict:
    """
    Функция для вычисления маршрута муравья k
    :param ant_k: муравей k
    :param mtr_adj: матрица смежности для графа
    :param mtr_phero: матрица феромонов
    :param mtr_visib: матрица видимости
    :param size: количество городов (размер матрицы)
    :param alpha: пар-р влияния видимости пути
    :param beta: пар-р влияния феромона
    :return: маршрут муравья k
    """

    while len(ant_k['tabu']) != size:
        nextCity = get_next_city(ant_k['tabu'], mtr_phero, mtr_visib, size, alpha, beta)

        ant_k['cost'] += mtr_adj[ant_k['tabu'][-1]][nextCity]
        ant_k['tabu'].append(nextCity)

    # незамкнутый маршрут - не добавляем в конец curr_route начальную вершину

    return ant_k


def update_phero(
        mtr_phero: np.ndarray,
        size: int,
        ants: list[dict],
        Q: float,
        evoparation: float
) -> np.ndarray:
    """
    Функция для обновления значения феромона по окончании дня
    :param mtr_phero: матрица феромонов
    :param size: количество городов (размер матрицы)
    :param ants: список маршрутов, пройденных всеми муравьями за 1 день
    :param Q: константа
    :param evoparation: коэф-т испарения
    :return: новая матрица феромонов
    """

    add_mtr_phero = np.zeros((size, size))

    for ant_k in ants:
        delta = Q / ant_k['cost']

        for i in range(size - 1):
            add_mtr_phero[ant_k['tabu'][i]][ant_k['tabu'][i + 1]] += delta

    mtr_phero += ((1 - evoparation) * mtr_phero + add_mtr_phero)

    for i in range(size):
        for j in range(size):
            mtr_phero[i][j] = 0.1 if mtr_phero[i][j] < MIN_PHEROMONE else mtr_phero[i][j]

    return mtr_phero


def ant_alg(
        mtr_adj: np.ndarray,
        size: int,
        alpha: float,
        beta: float,
        evoparation: float,
        cnt_days: int
):
    """
    Функция для реализации муравьиного алгоритма
    :param mtr_adj: матрица смежности для графа
    :param size: количество городов (размер матрицы)
    :param alpha: пар-р влияния видимости пути
    :param beta: пар-р влияния феромона
    :param evoparation: коэф-т испарения
    :param cnt_days: количество дней жизни колонии муравьев
    :return: маршрут min_route и его стоимость min_cost
    """

    Q: float = calc_Q(mtr_adj, size)

    min_route = list()
    min_cost = float("inf")

    mtr_phero: np.ndarray = init_mtr_phero(size)
    mtr_visib: np.ndarray = init_mtr_visib(mtr_adj, size)

    cnt_ants = size

    for day in range(cnt_days):
        ants: list[dict] = [{'tabu': [j], 'cost': 0} for j in range(cnt_ants)]

        for k in range(cnt_ants):
            ants[k]: dict = get_ant_route(ants[k], mtr_adj, mtr_phero, mtr_visib, size, alpha, beta)

            if ants[k]['cost'] < min_cost:
                min_cost = ants[k]['cost']
                min_route = ants[k]['tabu']

        mtr_phero = update_phero(mtr_phero, size, ants, Q, evoparation)

    return min_route, min_cost
