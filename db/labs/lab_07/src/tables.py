from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship
from sqlalchemy import Column, Integer, ForeignKey, Text, Numeric, CheckConstraint,  UniqueConstraint, Date, JSON, UUID, CHAR, VARCHAR, Boolean, REAL
from sqlalchemy import PrimaryKeyConstraint

Base = declarative_base()


class Doctors(Base):
    """
    Класс, представляющий таблицу докторов
    """
    __tablename__ = 'doctors'
    __table_args__ = {'schema': 'public'}

    id = Column(UUID, primary_key=True)
    fio = Column(Text, nullable=False)
    age = Column("age", Integer, CheckConstraint("age >= 27 and age <= 93"), nullable=False)
    gender = Column(CHAR, nullable=False)
    position = Column(VARCHAR(100), nullable=False)
    wage = Column(Integer, nullable=False)
    type_of_financ = Column(VARCHAR(10), nullable=False)
    empl_date = Column(Date, nullable=False)
    cabinet = Column(Integer, CheckConstraint("cabinet >= 1 and cabinet <= 1000"), nullable=False)
    mail = Column(VARCHAR(150), nullable=False)


class Patients(Base):
    """
    Класс, представляющий таблицу пациентов
    """
    __tablename__ = 'patients'
    __table_args__ = {'schema': 'public'}

    id = Column(UUID, primary_key=True)
    fio = Column(Text, nullable=False)
    date_of_birth = Column(Date, nullable=False)
    gender = Column(CHAR, nullable=False)
    age = Column(Integer, nullable=False)
    snils = Column(VARCHAR(14), nullable=False, unique=True)
    policy_oms = Column(VARCHAR(16), nullable=False, unique=True)
    address = Column(Text, nullable=False)
    phone = Column(VARCHAR(20), nullable=False, unique=True)
    empl = Column(Boolean, nullable=False)


class Diagnoses(Base):
    """
    Класс, представляющий таблицу диагнозов
    """
    __tablename__ = 'diagnoses'
    __table_args__ = {'schema': 'public'}

    id = Column(UUID, primary_key=True)
    name = Column(VARCHAR(100), nullable=False, unique=True)
    symptoms = Column(Text, nullable=False)
    risk_group = Column(VARCHAR(100), nullable=False)
    prob_of_death = Column("prob_of_death",REAL,CheckConstraint("prob_of_death >= 0 and prob_of_death <= 100"),  nullable=False)
    is_chronic = Column(Boolean, nullable=False)
    prob_of_relapse = Column("prob_of_relapse",REAL, CheckConstraint("prob_of_relapse >= 0 and prob_of_relapse <= 100"), nullable=False)


class Wards(Base):
    """
    Класс, представляющий таблицу палат
    """
    __tablename__ = 'wards'
    __table_args__ = {'schema': 'public'}

    id = Column(UUID, primary_key=True)
    number = Column("number", Integer, CheckConstraint("number >= 100"), nullable=False, unique=True)
    type = Column(VARCHAR(30), nullable=False)
    capacity = Column("capacity", Integer, CheckConstraint("capacity >= 1 and capacity <= 20"), nullable=False)
    engaged = Column(Integer, nullable=False)
    is_WC = Column(Boolean, nullable=False)
    is_full = Column(Boolean, nullable=False)


class Admissions(Base):
    """
    Класс, представляющий таблицу поступлений
    """
    __tablename__ = 'admissions'
    __table_args__ = {'schema': 'public'}

    id = Column(UUID, primary_key=True)
    number = Column("number", Integer, CheckConstraint("number >= 100"), nullable=False, unique=True)
    type = Column(VARCHAR(30), nullable=False)
    capacity = Column("capacity", Integer, CheckConstraint("capacity >= 1 and capacity <= 20"), nullable=False)
    engaged = Column(Integer, nullable=False)
    is_WC = Column(Boolean, nullable=False)
    is_full = Column(Boolean, nullable=False)


