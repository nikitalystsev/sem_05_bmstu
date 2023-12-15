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
        Получить среднюю зарплату неврологов
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

    def with_several_join_query(self):
        """
        Метод реализует запрос с несколькими join
        Найти всех врачей, у которых есть хотя бы один пациент с хроническим диагнозом
        """
        try:
            with self.__connection.cursor() as cursor:
                cursor.execute(
                    """
                    select *
                    from doctors as doc
                    where exists
                    (
                        select *
                        from admissions as adm
                        join patients as pat
                        on adm.id_pat = pat.id
                        join diagnoses as dia
                        on adm.id_dia = dia.id
                        where dia.is_chronic = true and doc.id = adm.id_doc
                    );
                    """
                )

                for row in cursor:
                    print(row)

        except Exception as _ex:
            print("[INFO] Ошибка выполнения запроса с несколькими join", _ex)

    def cte_row_number_query(self):
        """
        Метод реализует запрос с ОТВ(CTE) и оконными функциями
        Устранение полных дублей с помощью оконной функции row_number
        """
        try:
            with self.__connection.cursor() as cursor:
                cursor.execute(
                    """
                    with dupl as
                    ( 
                        select *
                        from admissions
                        
                        union all
                        
                        select *
                        from admissions
                    ), del_dupl as
                    (
                        select d.id, 
                            row_number() over (partition by d.id) as row_num
                        from dupl as d
                    )
                    
                    select *
                    from del_dupl
                    where row_num = 1;
                    """
                )

                for row in cursor:
                    print(row)

        except Exception as _ex:
            print("[INFO] Ошибка выполнения запроса с ОТВ(CTE) и оконными функциями", _ex)

    def metadata_query(self):
        """
        Метод реализует запрос к метаданным
        Вывести данные об типах и атрибутах таблицы patients
        """
        try:
            with self.__connection.cursor() as cursor:
                cursor.execute(
                    """
                    SELECT column_name, data_type
                    FROM information_schema.columns
                    WHERE table_name = 'patients';
                    """
                )

                for row in cursor:
                    print(row)

        except Exception as _ex:
            print("[INFO] Ошибка выполнения запроса к метаданным", _ex)

    def call_scalar_func_query(self):
        """
        Метод реализует вызов скалярной функции (написанной в третьей лабораторной работе);
        Вывести количество пациентов у конкретного доктора
        """
        try:
            with self.__connection.cursor() as cursor:
                cursor.execute(
                    """
                    select count_patients_by_doc('02bc8b61-b4eb-4227-adf1-031ce04d8a6d'); -- 3
                    """
                )

                for row in cursor:
                    print(row)

        except Exception as _ex:
            print("[INFO] Ошибка выполнения вызова скалярной функции", _ex)

    def call_multi_statement_or_table_query(self):
        """
        Метод реализует вызов многооператорной или табличной функции (написанной в третьей лабораторной работе);
        вывести более читаемые записи о поступлениях с диагнозами с вероятностью смерти менее переданного
        """
        try:
            with self.__connection.cursor() as cursor:
                cursor.execute(
                    """
                    select * 
                    from best_read_adm_less_death(70);
                    """
                )

                for row in cursor:
                    print(row)

        except Exception as _ex:
            print("[INFO] Ошибка выполнения вызова многооператорной или табличной функции", _ex)

    def call_stored_procedure_query(self):
        """
        Метод реализует вызов хранимой процедуры (написанной в третьей лабораторной работе);
        повысить зарплату всем врачам переданной в качестве параметра должности
        на 20 процентов от средней зарплате по этой же должности
        """
        try:
            with self.__connection.cursor() as cursor:
                cursor.execute(
                    """
                    call increase_wage_by_position('Диабетолог');
                    
                    select doc.fio, doc.position, doc.wage
                    from doctors as doc
                    where position = 'Диабетолог'
                    order by doc.wage;
                    """
                )

                for row in cursor:
                    print(row)

        except Exception as _ex:
            print("[INFO] Ошибка выполнения вызова хранимой процедуры", _ex)

    def call_system_procedure_query(self):
        """
        Метод реализует вызов системной процедуры;
        Получить версию сервера Postgresql
        """
        try:
            with self.__connection.cursor() as cursor:
                cursor.execute(
                    """
                    select version();
                    """
                )

                for row in cursor:
                    print(row)

        except Exception as _ex:
            print("[INFO] Ошибка выполнения вызова хранимой процедуры", _ex)

    def create_table_query(self):
        """
        Метод реализует запрос создания новой таблицы, соответствующей тематике БД
        Создать таблицу с лекарствами
        """
        try:
            with self.__connection.cursor() as cursor:
                cursor.execute(
                    """
                    create table if not exists medicines (
                        id uuid,
                        name varchar(20),
                        price integer
                    );
                    """
                )

                print("[INFO] Таблица с лекарствами была успешно создана")

        except Exception as _ex:
            print("[INFO] Ошибка выполнения вызова хранимой процедуры", _ex)

    def insert_medicines_query(self):
        """
        Метод реализует вставку данных в созданную таблицу с использованием инструкции INSERT или COPY

        """
        try:
            with self.__connection.cursor() as cursor:
                cursor.execute(
                    """
                    insert into medicines (name, price) 
                    values ('глицин', 100),
                            ('амброксол', 400)
                    """
                )

                print("[INFO] Данные в таблицу с лекарствами были успешно добавлены")

        except Exception as _ex:
            print("[INFO] Ошибка выполнения вызова хранимой процедуры", _ex)
