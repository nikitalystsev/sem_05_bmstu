import psycopg2

host = "127.0.0.1"
user = "nikitalystsev"
password = "zhpiix69"
db_name = "rk3"


class Rk3DB:
    def __init__(
            self,
            _host: str,
            _user: str,
            _password: str,
            _db_name: str
    ):
        """
        Инициализация атрибутов класса
        """
        try:
            self.__connection = psycopg2.connect(
                host=_host,
                user=_user,
                password=_password,
                database=_db_name
            )
            self.__connection.autocommit = True  # автоматическая фиксация транзакций

        except Exception as _ex:
            print("[INFO] Ошибка соединения с Postgresql", _ex)

    def __del__(self):
        """
        Метод вызывается с уничтожением объекта
        """
        if self.__connection:
            self.__connection.close()
            print("[INFO] Соединение с Postgresql закрыто")

    def query1(self):
        """
        Найти отдел, в котором работает самый молодой сотрудник (таких сотрудников м/б несколько)
        """
        try:
            with self.__connection.cursor() as cursor:
                cursor.execute(
                    """
                    select e._department AS youngest_employee_department
                    from employees as e
                    where e._date_of_birth = (select MAX(_date_of_birth) from employees);
                    """
                )

                for row in cursor:
                    print(row)

        except Exception as _ex:
            print("[INFO] Ошибка выполнения первого запроса", _ex)

    def query2(self):
        """
        Найти сотрудников, которые выходили с рабочего места более 3-х раз
        """
        try:
            with self.__connection.cursor() as cursor:
                cursor.execute(
                    """
                    select
                        e._id AS employee_id,
                        e._fio AS employee_name,
                        count(a._is_came) AS exits_count
                    from employees  as e
                    join accounting as a ON e._id = a._id
                    where a._is_came = 2
                    group by e._id, e._fio
                    having count(a._is_came) > 3;
                    """
                )

                for row in cursor:
                    print(row)

        except Exception as _ex:
            print("[INFO] Ошибка выполнения второго запроса", _ex)

    def query3(self):
        """
        Найти сотрудников, опоздавших не менее 7-ми раз
        """
        try:
            with self.__connection.cursor() as cursor:
                cursor.execute(
                    """
                    select
                        e._id AS employee_id,
                        e._fio AS employee_name,
                        count(case when a._is_came = 2 then 1 else null end) AS late_count
                    from employees as e
                    left join accounting as a on e._id = a._id
                    group by e._id, e._fio
                    having count(case when a._is_came = 2 then 1 else null end) >= 7;
                    """
                )

                for row in cursor:
                    print(row)

        except Exception as _ex:
            print("[INFO] Ошибка выполнения третьего запроса", _ex)


def main() -> None:
    """
    Главная функция
    """

    rk3_db = Rk3DB(host, user, password, db_name)

    # rk3_db.query1()

    # rk3_db.query2()

    rk3_db.query3()


if __name__ == "__main__":
    main()
