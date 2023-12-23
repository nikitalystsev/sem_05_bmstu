import sqlalchemy
from sqlalchemy import create_engine, select, insert, update, delete, func, text
from sqlalchemy.orm import Session, sessionmaker, class_mapper

from json import dumps, load

from models import *


# LINQ to Object
# 1. Вывести студента и его класс
def get_name_student(session):
    data = session.query(Student, Class).join(Class).all()
    print(data)
    for row in data:
        print((row.Student.firstname, '-', row.Class.Сlassnumber, row.Class.Сlassletter))


# 2. Вывести студентов, у которых есть итоговая 5
def get_student_mark_5(session):
    data = session.query(Student).join(Assessment).where(Assessment.finalassessment == 5).all()
    for row in data:
        print((row.studentid, row.firstname, row.genderstudent))


# 3. Вывести среднюю оценку
def get_avg_assessment(session):
    data = session.query(func.avg(Assessment.finalassessment).label("avg_assessment"))
    for row in data:
        print(row.avg_assessment)


# 4. Вывести количество студентов с каждой оценкой
def get_assessment_count_student(session):
    games_support = session.query(
        (Assessment.finalassessment).label("assessment"),
        func.count(Student.studentid).label('count_students'),
    ).join(Student).group_by(Assessment.finalassessment).all()
    for row in games_support:
        print((float(row.assessment), row.count_students))


# 5. Вывести студента и его среднюю оценку
def get_avg_mark_student(session):
    data = session.query(Student.firstname,
                         (((
                                   Assessment.firsttrimester + Assessment.secondtrimester + Assessment.thirdtrimester) / 3).label(
                             "final"))).join(Assessment).all()
    for row in data:
        print((row.firstname, float(row.final)))


# По названию предмета и дня недели вывести препо который ведет и кол-во обучающихся в соотв группе
def get_teacher_count_st(session):
    sub_name = 'Russian'  # input("Subject: ")
    day_name = 'Monday'  # input("Day: ")

    data = session.query(Teacher.firstname.label("firstname"), func.count(Student.studentid).label("cnt")).join(
        Schedule).join(Subject).join(Class).join(Student).where(
        Schedule.dayname == day_name and Subject.namesubject == sub_name
    ).group_by(Teacher.firstname).all()
    print(data)
    for row in data:
        print((row.firstname, row.cnt))
    new_data = [{"firstname": row.firstname, "cnt": row.cnt} for row in data]
    print(new_data)
    for row in new_data:
        row["firstname"] = str(row["firstname"])
        row["cnt"] = str(row["cnt"])

    with open('z.json', 'w') as f:
        f.write(dumps(new_data, indent=4))


# LINQ to JSON
# 1. Чтение из JSON.
def read_json():
    with open('subject.json') as f:
        subs = load(f)

    for sub in subs:
        print(sub)


# 2. Запись в Json
def table_to_json(model):
    columns = [c.key for c in class_mapper(model.__class__).columns]
    return dict((c, getattr(model, c)) for c in columns)


def subject_to_json(session):
    new_rows = [table_to_json(row) for row in session.query(Subject).order_by(Subject.subjectid).all()]

    for row in new_rows:
        row["subjectid"] = str(row["subjectid"])
        row["namesuгbject"] = str(row["namesubject"])

    with open('subject_new.json', 'w') as f:
        f.write(dumps(new_rows, indent=4))

    print("ОК")


# LINQ to SQL
# 1. Однотабличный запрос на выборку.
# Вывести студента и его итоговую оценку
def select_student_final_mark(session):
    res = session.execute(
        select(Assessment.studentid, Assessment.finalassessment)
    )

    for i in res:
        print((i.studentid, float(i.finalassessment)))


# 2. Многотабличный запрос на выборку.
# Вывести расписание уроков русского языка
def select_schedule_russian(session):
    res = session.execute(text(f"""
        Select * from (Select S1.dayname, S1.cabinet, S1.LessonNumber, S2.namesubject 
        from school.Schedule as S1
        join school.Subject as S2 on S1.subjectid = S2.subjectid
        order by S1.cabinet) as res 
        where res.namesubject = 'Russian'  
        """))
    for pl in res:
        print(pl)


# 3. Добавление данных в таблицу Subject
def insert_subject(session):
    try:
        name = input("Название предмета: ")

        count_games = session.query(func.count(Subject.subjectid)).all()
        subject_id = count_games[0][0] + 1

        session.execute(
            insert(Subject).values(
                subjectid=subject_id,
                namesubject=name
            )
        )
        session.commit()
        print("Данные успешно добавлены!")
    except:
        print("error input data")
        return


# 4. Обновление таблицы Subject
def update_subject(session):
    name = input("Старое название предмета: ")
    new_name = input("Новая название предмета: ")

    exists = session.query(
        session.query(Subject).where(Subject.namesubject == name).exists()
    ).scalar()

    if not exists:
        print("Такого предмета нет!")
        return

    session.execute(
        update(Subject).where(Subject.namesubject == name).values(namesubject=new_name)
    )
    session.commit()
    print("Данные успешно измененны!")


# 5. Удаление данных из Subject
def delete_subject(session):
    name = input("Название предмета для удаления: ")

    exists = session.query(
        session.query(Subject).where(Subject.namesubject == name).exists()
    ).scalar()

    if not exists:
        print("Такого предмета нет!")
        return

    session.execute(
        delete(Subject).where(Subject.namesubject == name)
    )
    session.commit()
    print("Данные успешно удалены!")


# Вывод таблицы Subject
def select_all_subject(session):
    games = session.query(Subject).order_by(Subject.subjectid).all()
    for g in games:
        print((g.subjectid, g.namesubject))


# 6. Хранимая процедура. Изменить оценку студента за первый триместр
def call_change_mark(session):
    id_s = int(input("Введите номер студента: "))
    mark = int(input("Введите новую оценку студента: "))
    data = session.execute(text('''CALL school.change_first_trimester({0}, {1});
            Select * from school.Assessment where studentId = 871;'''.format(id_s, mark)))

    for row in data:
        print(row)


MSG = "\n\t\t\tМеню\n" \
      "\t--------- LINQ to Object -------------- \n" \
      "\t5 запросов созданные для проверки LINQ\n" \
      "\t  1. Вывести студента и его класс.\n" \
      "\t  2. Вывести студентов, у которых есть итоговая 5.\n" \
      "\t  3. Вывести среднюю оценку.\n" \
      "\t  4. Вывести количество студентов с каждой оценкой.\n" \
      "\t  5. Вывести студента и его среднюю оценку.\n" \
      "\t--------- LINQ to JSON -------------- \n" \
      "\t  6. Чтение из JSON документа. \n" \
      "\t  7. Запись в JSON документ. \n" \
      "\t  8. Однотабличный запрос на выборку. (Вывести студента и его итоговую оценку)\n" \
      "\t  9. Многотабличный запрос на выборку. (Вывести расписание уроков русского языка)\n" \
      "\t 10. Добавление данных в таблицу Subject.\n" \
      "\t 11. Обновление данных в таблице Subject.\n" \
      "\t 12. Удаление данных из таблицы Subject.\n" \
      "\t 13. Вывод таблицы Subject.\n" \
      "\t 14. Вызов хранимой процедуры. (Изменить оценку студента за первый триместр).\n" \
      "\t 15. Защита.\n" \
      "\t0. Выход.\n" \
      "\tВыбор: "


def input_command():
    try:
        command = int(input(MSG))
        print()
    except:
        command = -1

    if command < 0 or command > 16:
        print("\nОжидался ввод целого числа от 0 до 15")

    return command


def main():
    engine = create_engine(
        f'postgresql://postgres:herogem2003@localhost:5432/schooldb',
        pool_pre_ping=True)
    try:
        engine.connect()
        print("БД school успешно подключена!")
    except:
        print("Ошибка подключения к БД!")
        return

    Session = sessionmaker(bind=engine)
    session = Session()
    command = -1

    while command != 0:
        command = input_command()

        if command == 1:
            get_name_student(session)
        elif command == 2:
            get_student_mark_5(session)
        elif command == 3:
            get_avg_assessment(session)
        elif command == 4:
            get_assessment_count_student(session)
        elif command == 5:
            get_avg_mark_student(session)
        elif command == 6:
            read_json()
        elif command == 7:
            subject_to_json(session)
        elif command == 8:
            select_student_final_mark(session)
        elif command == 9:
            select_schedule_russian(session)
        elif command == 10:
            insert_subject(session)
        elif command == 11:
            update_subject(session)
        elif command == 12:
            delete_subject(session)
        elif command == 13:
            select_all_subject(session)
        elif command == 14:
            call_change_mark(session)
        elif command == 15:
            get_teacher_count_st(session)
        else:
            continue


if __name__ == "__main__":
    main()
