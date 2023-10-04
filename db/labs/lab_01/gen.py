from faker import Faker

from config import *

COUNT_RECORDS = 10


class Generator:
    """Класс для генерации данных"""

    def __init__(self):
        """Инициализация"""

        self.diagnoses = Diagnoses()
        self.titles_hosp = TitlesHospitals()
        self.titles_dep = TitlesDepartment()

    def gen_hospital(self):
        """Функция генерирует больницу"""
        faker = Faker("ru_RU")

        with open("./data/Больницы.txt", "w") as file:
            for i in range(COUNT_RECORDS):
                id_hosp = faker.unique.random_int(1, COUNT_RECORDS)
                title_hosp = self.titles_hosp[i]
                address = faker.address()
                head_physician = faker.name()
                phone = faker.phone_number()

                res = f"{id_hosp} {title_hosp} {address} {head_physician} {phone}\n"

                file.write(res)

    def gen_department(self):
        """Функция генерирует отделение"""
        faker2 = Faker("ru_RU")
        with open("./data/Отделения.txt", "w") as file:
            for i in range(COUNT_RECORDS):  # идем по больницам
                faker_floor = Faker("ru_RU")
                for j in range(len(self.titles_dep)):  # идем по отделениям
                    id_dep = faker2.unique.random_int(1, COUNT_RECORDS * len(self.titles_dep))
                    title_dep = self.titles_dep[j]
                    floor_num = faker_floor.unique.random_int(1, len(self.titles_dep))
                    ward_num = rd.randint(1, 50)

                    res = f"{id_dep} {i} {title_dep} {floor_num} {ward_num} \n"

                    file.write(res)

    def gen_doctor(self):
        """Функция генерирует доктора"""
        faker = Faker("ru_RU")

        with open("./data/Врачи.txt", "w") as file:
            for i in range(COUNT_RECORDS):  # идем по всем возможным отделениям
                id_doctor = faker.unique.random_int(1, COUNT_RECORDS)
                fio_doctor = faker.name()
                speciality = rd.choice(rd.choice(
                    [self.recovery, self.specialists, self.genitourinary, self.oncological, self.psychoneurological,
                     self.dentistry, self.therapeutic, self.surgery]))
                gender = "F" if fio_doctor.split()[0][-1] in "аеиоуыэюя" else "M"
                financing = rd.choice(["бюджет", "платный"])

                res = f"{id_doctor} {fio_doctor} {speciality} {gender} {financing}\n"

                file.write(res)

    @staticmethod
    def gen_patient():
        """Функция генерирует пациента"""
        faker = Faker("ru_RU")

        with open("./data/Пациенты.txt", "w") as file:
            for i in range(COUNT_RECORDS):  # идем по всем возможным отделениям
                id_pat = faker.unique.random_int(1, COUNT_RECORDS)
                fio_pat = faker.name()
                birthday = faker.date()
                gender = "F" if fio_pat.split()[0][-1] in "аеиоуыэюя" else "M"
                address = faker.address()
                phone = faker.phone_number()

                res = f"{id_pat} {fio_pat} {birthday} {gender} {address} {phone}\n"

                file.write(res)


def main():
    """Главная функция"""
    gen_obj = Generator()

    gen_obj.gen_hospital()
    gen_obj.gen_department()
    gen_obj.gen_doctor()
    gen_obj.gen_patient()


if __name__ == '__main__':
    main()
