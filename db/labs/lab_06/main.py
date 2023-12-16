from config import host, user, password, db_name
from hospital_db import HospitalDB

MENU = """
\t\tМЕНЮ
1  -- выполнить скалярный запрос;
2  -- выполнить запрос с несколькими соединениями;
3  -- выполнить запрос с ОТВ и оконными функциями;
4  -- выполнить запрос к метаданным;
5  -- вызвать скалярную функцию;
6  -- вызвать табличную функцию;
7  -- вызвать хранимую процедуру;
8  -- вызвать системную функцию;
9  -- создать таблицу;
10 -- выполнить вставку данных;
0  -- выход.

Выбор: """


def input_command():
    try:
        command = int(input(MENU))
        print()
    except Exception:
        command = -1

    if command < 0 or command > 10:
        print("Ожидался ввод целого числа от 0 до 10")

    return command


def print_table(table):
    if table is not None:
        for row in table:
            print(row)


def main() -> None:
    """
    Главная функция
    """
    hospital_db = HospitalDB(
        host=host,
        user=user,
        password=password,
        db_name=db_name
    )

    command = -1

    while command != 0:
        command = input_command()

        if command == 1:
            table = hospital_db.scalar_query()

        elif command == 2:
            table = hospital_db.with_several_join_query()

        elif command == 3:
            table = hospital_db.cte_row_number_query()

        elif command == 4:
            table = hospital_db.metadata_query()

        elif command == 5:
            table = hospital_db.call_scalar_func_query()

        elif command == 6:
            table = hospital_db.call_multi_statement_or_table_query()

        elif command == 7:
            table = hospital_db.call_stored_procedure_query()

        elif command == 8:
            table = hospital_db.call_system_procedure_query()

        elif command == 9:
            table = hospital_db.create_table_query()

        elif command == 10:
            table = hospital_db.insert_medicines_query()
        else:
            continue

        print_table(table)


if __name__ == "__main__":
    main()
