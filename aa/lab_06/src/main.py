import utils
import measurements as mea


def main():
    """
    Главная функция
    :return: None
    """
    option = -1
    while option != 0:
        try:
            option = int(input("Меню\n\
                1. Полный перебор \n\
                2. Муравьиный алгоритм \n\
                3. Все алгоритмы \n\
                4. Параметризация \n\
                5. Замерить время \n\
                6. Обновить данные \n\
                7. Распечатать матрицу \n\
                0. Выход \n\
                Выбор: "))
        except ValueError:
            option = -1

        match option:
            case 1:
                utils.parse_brute_force_alg()
            case 2:
                utils.parse_ant_alg()
            case 3:
                utils.parse_all()
            case 4:
                pass
                # parametrization(type=CSV)
            case 5:
                mea.test_time()
            case 6:
                utils.update_file()
            case 7:
                utils.print_mtr_adj()
            case 0:
                print("Спасибо, что пользовались этой программой!")
            case _:
                print("Повторите ввод")


if __name__ == '__main__':
    main()
