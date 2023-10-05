import csv
from faker import Faker

from config import *


class Generator:
    """Класс для генерации данных"""

    def __init__(self, count_record: int):
        """Инициализация"""

        self.count_record = count_record
        self.diagnoses = Diagnoses()
        self.symptoms = Symptoms()
        self.speciality = Speciality()
        self.risk_groups = RiskGroups()
        self.type_wards = TypeWards()

        self.docs_id = []
        self.pats_id = []
        self.dias_id = []
        self.wards_id = []

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

            for i in range(self.count_record):
                id_doc = faker.unique.uuid4()
                fio_doc = faker.name()
                age = rd.randint(27, 93)
                speciality = rd.choice(self.speciality)
                gender = "Ж" if fio_doc.split()[0][-1] in "аеиоуыэюя" else "М"
                type_of_financ = rd.choice(["бюджет", "платный"])
                employment_date = faker.date()
                cabinet = rd.randint(1, 1000)
                office_mail = faker.company_email()

                writer.writerow(
                    [id_doc, fio_doc, age, speciality, gender, type_of_financ, employment_date, cabinet,
                     office_mail])

                self.docs_id.append(id_doc)

    def __gen_patients(self):
        """Функция генерирует пациента"""
        faker = Faker("ru_RU")

        with open("../data/patients.csv", "w", newline='') as file:
            writer = csv.writer(file, delimiter=',')

            for i in range(self.count_record):  # идем по всем возможным отделениям
                id_pat = faker.unique.uuid4()
                fio_pat = faker.name()
                date_of_birth = faker.date()
                gender = "Ж" if fio_pat.split()[0][-1] in "аеиоуыэюя" else "М"
                snils = self.gen_snils()
                policy_oms = self.generate_oms_policy_number()
                address_pat = faker.address()
                phone_number = faker.phone_number()
                employment = rd.choice([True, False])
                writer.writerow(
                    [id_pat, fio_pat, date_of_birth, gender, snils, policy_oms, address_pat, phone_number, employment])

                self.pats_id.append(id_pat)

    def __gen_diagnoses(self):
        """Функция генерирует диагнозы"""
        faker = Faker("ru_RU")

        with open("../data/diagnoses.csv", "w", newline='') as file:
            writer = csv.writer(file, delimiter=',')

            for i in range(1002):  # количество диагнозов
                id_dia = faker.unique.uuid4()
                title = self.diagnoses[i]
                symptoms = f"{rd.choice(self.symptoms)} {rd.choice(self.symptoms)}"
                risk_group = rd.choice(self.risk_groups)
                probability_of_death = str(round(rd.uniform(0, 100), 2))
                is_chronic = rd.choice([True, False])
                probability_of_relapse = str(round(rd.uniform(0, 100), 2))

                writer.writerow([id_dia, title, symptoms, risk_group, probability_of_death,
                                 is_chronic, probability_of_relapse])

                self.dias_id.append(id_dia)

    def __gen_wards(self):
        """Функция генерирует палату"""
        faker = Faker("ru_RU")

        with open("../data/wards.csv", "w", newline='') as file:
            writer = csv.writer(file, delimiter=',')

            numbers = list(range(100, self.count_record + 1000))
            rd.shuffle(numbers)

            for i in range(self.count_record):  # количество диагнозов
                id_ward = faker.unique.uuid4()
                number = numbers[i]
                type_ward = rd.choice(self.type_wards)
                capacity = rd.randint(1, 10)
                is_wc = rd.choice([True, False])
                is_full = rd.choice([True, False])

                writer.writerow([id_ward, number, type_ward, capacity, is_wc, is_full])

                self.wards_id.append(id_ward)

    def __gen_admissions(self):
        """Функция генерирует поступления"""
        faker = Faker("ru_RU")

        with open("../data/admissions.csv", "w", newline='') as file:
            writer = csv.writer(file, delimiter=',')

            already_was_dict = dict()

            for i in range(self.count_record):  # количество диагнозов
                id_adm = faker.unique.uuid4()
                id_pac = rd.choice(self.pats_id)
                id_doc = rd.choice(self.docs_id)
                is_dia = rd.choice(self.dias_id)
                id_ward = rd.choice(self.wards_id)
                date_adm = faker.date()
                ambulatory_treatment = rd.choice([True, False])
                term = rd.randint(1, 365)
                already_was = ''

                for key in already_was_dict:
                    if id_pac == key:  # если уже когда-то поступал
                        already_was = already_was_dict[key]

                already_was_dict[id_pac] = id_adm

                writer.writerow([id_adm, id_pac, id_doc, is_dia, id_ward, date_adm,
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
