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
            self._connection = psycopg2.connect(
                host=host,
                user=user,
                password=password,
                database=db_name
            )
        except Exception as _ex:
            print("[INFO] Ошибка соединения с Postgresql", _ex)

    def __del__(self):
        """
        Метод вызывается с уничтожением объекта
        """
        if self._connection:
            self._connection.close()
            print("[INFO] Соединение с Postgresql закрыто")
