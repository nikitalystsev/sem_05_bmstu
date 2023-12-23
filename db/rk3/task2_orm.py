from sqlalchemy import Column, Integer, ForeignKey, Text, Date, VARCHAR, TIME
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()


class Employees(Base):
    """
    Класс, представляющий таблицу сотрудников
    """
    __tablename__ = 'employees'
    __table_args__ = {'schema': 'public'}

    _id = Column("_id", Integer, primary_key=True)
    _fio = Column("_fio", Text)
    _date_of_birth = Column("_date_of_birth", Date)
    _department = Column("_department", Text)


class Accounting(Base):
    """
    Класс, представляющий учета прохода сотрудников через КПП
    """
    __tablename__ = 'accounting'
    __table_args__ = {'schema': 'public'}

    _id = Column("_id", Integer, ForeignKey("public.employees._id"))
    _date = Column("_date", Date)
    _day_week = Column("_day_week", VARCHAR(15))
    _department = Column("_department", Text)
    _time = Column("_time", TIME)
    _is_came = Column("_is_came", Integer)
