import random as rd


class BaseData:
    """Класс данных"""

    def __init__(self, file_department: str):
        """Инициализация"""
        self.__speciality = list()

        with open(file_department) as file:
            self.__speciality = file.readlines()

        for i in range(len(self.__speciality)):
            self.__speciality[i] = self.__speciality[i].rstrip('\n')

        rd.shuffle(self.__speciality)

    def __getitem__(self, item):
        """Возвращение по ключу"""
        if 0 <= item < len(self.__speciality):
            return self.__speciality[item]
        else:
            raise IndexError("Неверный индекс")

    def __len__(self):
        return len(self.__speciality)


class Recovery(BaseData):
    """Восстановление и реабилитация"""

    def __init__(self):
        """Инициализация"""
        super().__init__("./data_for_gen/Восстановление_и_реабилитация.txt")


class Specialists(BaseData):
    """Врачи специалисты"""

    def __init__(self):
        """Инициализация"""
        super().__init__("./data_for_gen/Врачи_специалисты.txt")


class Genitourinary(BaseData):
    """Врачи специалисты"""

    def __init__(self):
        """Инициализация"""
        super().__init__("./data_for_gen/Мочеполовая_система.txt")


class Oncological(BaseData):
    """Онкологический профиль"""

    def __init__(self):
        """Инициализация"""
        super().__init__("./data_for_gen/Онкологический_профиль.txt")


class Psychoneurological(BaseData):
    """Психоневрологический профиль"""

    def __init__(self):
        """Инициализация"""
        super().__init__("./data_for_gen/Психоневрологический_профиль.txt")


class Dentistry(BaseData):
    """Стоматология"""

    def __init__(self):
        """Инициализация"""
        super().__init__("./data_for_gen/Стоматология.txt")


class Therapeutic(BaseData):
    """Терапевтический профиль и узкие специалисты"""

    def __init__(self):
        """Инициализация"""
        super().__init__("./data_for_gen/Терапевтический_профиль_и_узкие_специалисты.txt")


class Surgery(BaseData):
    """Хирургия"""

    def __init__(self):
        """Инициализация"""
        super().__init__("./data_for_gen/Хирургия.txt")


class Diagnoses(BaseData):
    """Диагнозы"""

    def __init__(self):
        """Инициализация"""
        super().__init__("./data_for_gen/Диагнозы.txt")


class TitlesHospitals(BaseData):
    """Названия больниц"""

    def __init__(self):
        """Инициализация"""
        super().__init__("./data_for_gen/Названия_больниц.txt")


class TitlesDepartment(BaseData):
    """Названия больниц"""

    def __init__(self):
        """Инициализация"""
        super().__init__("./data_for_gen/Названия_отделений.txt")
