import csv
from faker import Faker

from config import *


class Generator:
    """Класс для генерации данных"""

    def __init__(self, count_record: int):
        """Инициализация"""

        self.__count_record = count_record
        self.__diagnoses = Diagnoses()
        self.__symptoms = Symptoms()
        self.__speciality = Speciality()
        self.__risk_groups = RiskGroups()
        self.__type_wards = TypeWards()

        self.__docs_id = []
        self.__pats_id = []
        self.__dias_id = []
        self.__wards_id = []

    @staticmethod
    def gen_snils():
        # Генерируем случайные числа для СНИЛС
        snils_digits = [rd.randint(0, 9) for _ in range(9)]

        # Рассчитываем контрольное число
        checksum = sum((i + 1) * digit for i, digit in enumerate(snils_digits)) % 101
        if checksum < 10:
            snils_digits.append(checksum)
        else:
            snils_digits.extend([0, checksum - 100])

        # Форматируем СНИЛС в строку
        snils = ''.join(map(str, snils_digits))

        # Добавляем разделители
        snils = f'{snils[:3]}-{snils[3:6]}-{snils[6:9]} {snils[11:]}'

        return snils

    @staticmethod
    def generate_oms_policy_number():
        # Генерируем случайный номер полиса
        oms_number = ''.join([str(rd.randint(0, 9)) for _ in range(16)])

        # Форматируем номер с разделителями
        formatted_oms_number = f'{oms_number[:3]}{oms_number[3:7]}{oms_number[7:11]}{oms_number[11:]}'

        return formatted_oms_number

    def __gen_doctors(self):
        """Функция генерирует доктора"""
        faker = Faker("ru_RU")

        with open("../data/doctors.csv", "w", newline='') as file:
            writer = csv.writer(file, delimiter=',')

            for i in range(self.__count_record):
                id = faker.unique.uuid4()
                fio = faker.name()
                age = rd.randint(27, 93)
                gender = "Ж" if fio.split()[0][-1] in "аеиоуыэюя" else "М"
                position = rd.choice(self.__speciality)
                wage = rd.randint(40000, 240000)
                type_of_financ = rd.choice(["бюджет", "платный"])
                empl_date = faker.date()
                cabinet = rd.randint(1, 1000)
                mail = faker.company_email()

                writer.writerow(
                    [id, fio, age, gender, position, wage, type_of_financ, empl_date, cabinet,
                     mail])

                self.__docs_id.append(id)

    def __gen_patients(self):
        """Функция генерирует пациента"""
        faker = Faker("ru_RU")

        with open("../data/patients.csv", "w", newline='') as file:
            writer = csv.writer(file, delimiter=',')

            for i in range(self.__count_record):  # идем по всем возможным отделениям
                id = faker.unique.uuid4()
                fio = faker.name()
                date_of_birth = faker.date()
                gender = "Ж" if fio.split()[0][-1] in "аеиоуыэюя" else "М"
                age = rd.randint(0, 105)
                snils = self.gen_snils()
                policy_oms = self.generate_oms_policy_number()
                address = faker.address()
                phone = faker.phone_number()
                empl = rd.choice([True, False])
                writer.writerow(
                    [id, fio, date_of_birth, gender, age, snils, policy_oms, address, phone, empl])

                self.__pats_id.append(id)

    def __gen_diagnoses(self):
        """Функция генерирует диагнозы"""
        faker = Faker("ru_RU")

        with open("../data/diagnoses.csv", "w", newline='') as file:
            writer = csv.writer(file, delimiter=',')

            for i in range(1002):  # количество диагнозов
                id = faker.unique.uuid4()
                name = self.__diagnoses[i]
                symptoms = f"{rd.choice(self.__symptoms)} {rd.choice(self.__symptoms)}"
                risk_group = rd.choice(self.__risk_groups)
                prob_of_death = str(round(rd.uniform(0, 100), 2))
                is_chronic = rd.choice([True, False])
                prob_of_relapse = str(round(rd.uniform(0, 100), 2))

                writer.writerow([id, name, symptoms, risk_group, prob_of_death,
                                 is_chronic, prob_of_relapse])

                self.__dias_id.append(id)

    def __gen_wards(self):
        """Функция генерирует палату"""
        faker = Faker("ru_RU")

        with open("../data/wards.csv", "w", newline='') as file:
            writer = csv.writer(file, delimiter=',')

            numbers = list(range(100, self.__count_record + 1000))
            rd.shuffle(numbers)

            for i in range(self.__count_record):  # количество диагнозов
                id_ward = faker.unique.uuid4()
                number = numbers[i]
                type_ward = rd.choice(self.__type_wards)
                capacity = rd.randint(1, 20)
                engaged = rd.randint(0, capacity)
                is_wc = rd.choice([True, False])
                is_full = rd.choice([True, False])

                writer.writerow([id_ward, number, type_ward, capacity, engaged, is_wc, is_full])

                self.__wards_id.append(id_ward)

    def __gen_admissions(self):
        """Функция генерирует поступления"""
        faker = Faker("ru_RU")

        with open("../data/admissions.csv", "w", newline='') as file:
            writer = csv.writer(file, delimiter=',')

            already_was_dict = dict()

            for i in range(self.__count_record):  # количество диагнозов
                id = faker.unique.uuid4()
                id_pac = rd.choice(self.__pats_id)
                id_doc = rd.choice(self.__docs_id)
                is_dia = rd.choice(self.__dias_id)
                id_ward = rd.choice(self.__wards_id)
                date_adm = faker.date()
                ambulatory_treatment = rd.choice([True, False])
                term = rd.randint(1, 365)
                already_was = ''

                for key in already_was_dict:
                    if id_pac == key:  # если уже когда-то поступал
                        already_was = already_was_dict[key]

                already_was_dict[id_pac] = id

                writer.writerow([id, id_pac, id_doc, is_dia, id_ward, date_adm,
                                 ambulatory_treatment, term, already_was])

    def gen_data(self):
        """Функция генерирует все данные"""
        self.__gen_doctors()
        self.__gen_patients()
        self.__gen_diagnoses()
        self.__gen_wards()
        self.__gen_admissions()


def main():
    """Главная функция"""
    gen_obj = Generator(5000)
    gen_obj.gen_data()


if __name__ == '__main__':
    main()
