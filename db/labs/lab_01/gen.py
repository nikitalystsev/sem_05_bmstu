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

    def gen_doctors(self):
        """Функция генерирует доктора"""
        faker = Faker("ru_RU")

        with open("./data/doctors.csv", "w", newline='') as file:
            writer = csv.writer(file, delimiter=',')

            for i in range(self.count_record):
                id_doc = faker.unique.uuid4()
                fio_doc = faker.name()
                speciality = rd.choice(self.speciality)
                gender = "Ж" if fio_doc.split()[0][-1] in "аеиоуыэюя" else "М"
                financing = rd.choice(["бюджет", "платный"])

                writer.writerow([id_doc, fio_doc, speciality, gender, financing])

                self.docs_id.append(id_doc)

    def gen_patients(self):
        """Функция генерирует пациента"""
        faker = Faker("ru_RU")

        with open("./data/patients.csv", "w", newline='') as file:
            writer = csv.writer(file, delimiter=',')

            for i in range(self.count_record):  # идем по всем возможным отделениям
                id_pat = faker.unique.uuid4()
                fio_pat = faker.name()
                date_of_birth = faker.date()
                gender = "Ж" if fio_pat.split()[0][-1] in "аеиоуыэюя" else "М"
                address = faker.address()
                phone_number = faker.phone_number()

                writer.writerow([id_pat, fio_pat, date_of_birth, gender, address, phone_number])

                self.pats_id.append(id_pat)

    def gen_diagnoses(self):
        """Функция генерирует диагнозы"""
        faker = Faker("ru_RU")

        with open("./data/diagnoses.csv", "w", newline='') as file:
            writer = csv.writer(file, delimiter=',')

            for i in range(1046):  # количество диагнозов
                id_dia = faker.unique.uuid4()
                title = self.diagnoses[i]
                symptoms = f"{rd.choice(self.symptoms)} {rd.choice(self.symptoms)}"
                risk_group = rd.choice(self.risk_groups)
                probability_of_death = str(round(rd.uniform(0, 100), 2)) + "%"
                is_chronic = rd.choice([True, False])
                probability_of_relapse = str(round(rd.uniform(0, 100), 2)) + "%"

                writer.writerow([id_dia, title, symptoms, risk_group, probability_of_death,
                                 is_chronic, probability_of_relapse])

                self.dias_id.append(id_dia)

    def gen_wards(self):
        """Функция генерирует палату"""
        faker = Faker("ru_RU")

        with open("./data/wards.csv", "w", newline='') as file:
            writer = csv.writer(file, delimiter=',')

            numbers = list(range(100, self.count_record + 1000))
            rd.shuffle(numbers)

            for i in range(self.count_record):  # количество диагнозов
                id_ward = faker.unique.uuid4()
                number = numbers[i]
                type_cham = rd.choice(self.type_wards)
                capacity = rd.randint(1, 10)
                is_wc = rd.choice([True, False])
                is_full = rd.choice([True, False])

                writer.writerow([id_ward, number, type_cham, capacity, is_wc, is_full])

                self.wards_id.append(id_ward)

    def gen_admissions(self):
        """Функция генерирует поступления"""
        faker = Faker("ru_RU")

        with open("./data/admissions.csv", "w", newline='') as file:
            writer = csv.writer(file, delimiter=',')

            for i in range(self.count_record):  # количество диагнозов
                id_adm = faker.unique.uuid4()
                id_pac = rd.choice(self.pats_id)
                id_doc = rd.choice(self.docs_id)
                date_adm = faker.date()
                is_dia = rd.choice(self.dias_id)
                ambulatory_treatment = rd.choice([True, False])
                id_ward = rd.choice(self.wards_id)

                writer.writerow([id_adm, id_pac, id_doc, date_adm,
                                 is_dia, ambulatory_treatment, id_ward])


def main():
    """Главная функция"""
    gen_obj = Generator(5000)

    gen_obj.gen_doctors()
    gen_obj.gen_patients()
    gen_obj.gen_diagnoses()
    gen_obj.gen_wards()
    gen_obj.gen_admissions()


if __name__ == '__main__':
    main()
