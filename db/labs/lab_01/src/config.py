import random as rd


class BaseData:
    """Класс данных"""

    def __init__(self, file_department: str):
        """Инициализация"""
        self.__data = list()

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


class Diagnoses(BaseData):
    """Диагнозы"""

    def __init__(self):
        """Инициализация"""
        super().__init__("../data_for_gen/diagnoses.txt")


class Symptoms(BaseData):
    """Симптомы"""

    def __init__(self):
        """Инициализация"""
        super().__init__("../data_for_gen/symptoms.txt")


class Speciality(BaseData):
    """Специальности"""

    def __init__(self):
        """Инициализация"""
        super().__init__("../data_for_gen/speciality.txt")


class RiskGroups(BaseData):
    """Группы риска"""

    def __init__(self):
        """Инициализация"""
        super().__init__("../data_for_gen/risk_group.txt")


class TypeWards(BaseData):
    """Типы палат"""

    def __init__(self):
        """Инициализация"""
        super().__init__("../data_for_gen/type_wards.txt")
