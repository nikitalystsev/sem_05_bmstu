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
        self.type_chams = TypeChams()

    def gen_doctors(self):
        """Функция генерирует доктора"""
        faker = Faker("ru_RU")

        with open("./data/doctors.txt", "w") as file:
            all_data_doc = list()

            ids = list(range(1, self.count_record + 1))
            rd.shuffle(ids)

            for i in range(self.count_record):
                id_doc = ids[i]
                fio_doc = faker.name()
                speciality = rd.choice(self.speciality)
                gender = "Ж" if fio_doc.split()[0][-1] in "аеиоуыэюя" else "М"
                financing = rd.choice(["бюджет", "платный"])

                all_data_doc.append([id_doc, fio_doc, speciality, gender, financing])

            all_data_doc.sort(key=lambda a: a[0])

            file.writelines(' '.join(map(str, lst)) + '\n' for lst in all_data_doc)

    def gen_patients(self):
        """Функция генерирует пациента"""
        faker = Faker("ru_RU")

        with open("./data/patients.txt", "w") as file:
            all_data_pat = list()

            ids = list(range(1, self.count_record + 1))
            rd.shuffle(ids)

            for i in range(self.count_record):  # идем по всем возможным отделениям
                id_pat = ids[i]
                fio_pat = faker.name()
                date_of_birth = faker.date()
                gender = "Ж" if fio_pat.split()[0][-1] in "аеиоуыэюя" else "М"
                address = faker.address()
                phone_number = faker.phone_number()

                all_data_pat.append([id_pat, fio_pat, date_of_birth, gender, address, phone_number])

            all_data_pat.sort(key=lambda a: a[0])

            file.writelines(' '.join(map(str, lst)) + '\n' for lst in all_data_pat)

    def gen_diagnoses(self):
        """Функция генерирует диагнозы"""

        with open("./data/diagnoses.txt", "w") as file:
            all_data_dia = list()

            for i in range(1025):  # количество диагнозов
                id_dia = i + 1
                title = self.diagnoses[i]
                symptoms = f"{rd.choice(self.symptoms)} {rd.choice(self.symptoms)}"
                risk_group = rd.choice(self.risk_groups)
                probability_of_death = str(round(rd.uniform(0, 100), 2)) + "%"
                is_chronic = rd.choice([True, False])
                probability_of_relapse = str(round(rd.uniform(0, 100), 2)) + "%"

                all_data_dia.append([id_dia, title, symptoms, risk_group, probability_of_death,
                                     is_chronic, probability_of_relapse])

            all_data_dia.sort(key=lambda a: a[0])

            file.writelines(', '.join(map(str, lst)) + '\n' for lst in all_data_dia)

    def gen_chambers(self):
        """Функция генерирует палату"""

        with open("./data/chambers.txt", "w") as file:
            all_data_cham = list()

            ids = list(range(1, self.count_record + 1))
            rd.shuffle(ids)

            numbers = list(range(100, self.count_record + 1000))
            rd.shuffle(ids)

            for i in range(self.count_record):  # количество диагнозов
                id_cham = ids[i]
                number = numbers[i]
                type_cham = rd.choice(self.type_chams)
                capacity = rd.randint(1, 10)
                is_wc = rd.choice([True, False])
                is_full = rd.choice([True, False])

                all_data_cham.append([id_cham, number, type_cham, capacity, is_wc, is_full])

            all_data_cham.sort(key=lambda a: a[0])

            file.writelines(', '.join(map(str, lst)) + '\n' for lst in all_data_cham)

    def gen_admissions(self):
        """Функция генерирует поступления"""
        faker = Faker("ru_RU")

        with open("./data/admissions.txt", "w") as file:
            all_data_adm = list()

            ids = list(range(1, self.count_record + 1))
            rd.shuffle(ids)

            for i in range(self.count_record):  # количество диагнозов
                id_adm = ids[i]
                id_pac = rd.choice(ids)
                id_doc = rd.choice(ids)
                date_adm = faker.date()
                is_dia = rd.choice(list(range(1, 1026)))
                ambulatory_treatment = rd.choice([True, False])
                id_cham = rd.choice(ids)

                all_data_adm.append([id_adm, id_pac, id_doc, date_adm, is_dia, ambulatory_treatment, id_cham])

            all_data_adm.sort(key=lambda a: a[0])

            file.writelines(', '.join(map(str, lst)) + '\n' for lst in all_data_adm)


def main():
    """Главная функция"""
    gen_obj = Generator(5000)

    gen_obj.gen_doctors()
    gen_obj.gen_patients()
    gen_obj.gen_diagnoses()
    gen_obj.gen_chambers()
    gen_obj.gen_admissions()


if __name__ == '__main__':
    main()
