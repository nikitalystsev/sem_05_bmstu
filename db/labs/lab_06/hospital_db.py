import psycopg2


class HospitalDB:
    def __init__(
            self,
            host: str,
            user: str,
            password: str,
            db_name: str
    ):
        """
        Инициализация атрибутов класса
        """
        try:
            self.__connection = psycopg2.connect(
                host=host,
                user=user,
                password=password,
                database=db_name
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

    def scalar_query(self):
        """
        Метод реализует скалярный запрос
        """
        try:
            with self.__connection.cursor() as cursor:
                cursor.execute(
                    """
                    select avg(wage)
                    from doctors as doc
                    where doc.position = 'Невролог';
                    """
                )

                print(cursor.fetchone())

        except Exception as _ex:
            print("[INFO] Ошибка выполнения скалярного запроса", _ex)
