from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship
from sqlalchemy import Column, Integer, ForeignKey, Text, Numeric, CheckConstraint, Date, JSON
from sqlalchemy import PrimaryKeyConstraint

Base = declarative_base()


class Class(Base):
    __tablename__ = 'class'
    __table_args__ = {"schema": "school"}
    classid = Column(Integer, primary_key=True)
    Сlassletter = Column(Text, nullable=False)
    Сlassnumber = Column('Сlassnumber', Integer,
                         CheckConstraint("Сlassnumber >= 1 and Сlassnumber <= 11"), nullable=False)


class Student(Base):
    __tablename__ = 'student'
    __table_args__ = {"schema": "school"}
    studentid = Column(Integer, primary_key=True)
    firstname = Column(Text, nullable=False)
    genderstudent = Column(Text, nullable=False)
    ClassId = Column('classid', Integer, ForeignKey('school.class.classid'))

    class_id = relationship("Class", foreign_keys=[ClassId])

class Teacher(Base):
    __tablename__ = 'teacher'
    __table_args__ = {"schema": "school"}
    teacherid = Column(Integer, primary_key=True)
    firstname = Column(Text, nullable=False)
    genderteacher = Column(Text, nullable=False)
    cabinet = Column(Integer, nullable=False)


class Subject(Base):
    __tablename__ = 'subject'
    __table_args__ = {"schema": "school"}
    subjectid = Column(Integer, primary_key=True)
    namesubject = Column(Text, nullable=False)


class Schedule(Base):
    __tablename__ = 'schedule'
    __table_args__ = (PrimaryKeyConstraint('classid', 'subjectid', 'teacherid'), {"schema": "school"})

    dayname = Column(Text, nullable=False)
    ClassId = Column('classid', Integer, ForeignKey('school.class.classid', ondelete="CASCADE"))
    SubjectId = Column('subjectid', Integer, ForeignKey('school.subject.subjectid', ondelete="CASCADE"))
    teacherid = Column('teacherid', Integer, ForeignKey('school.teacher.teacherid', ondelete="CASCADE"))
    cabinet = Column(Integer, nullable=False)
    lesson_number = Column(Integer, nullable=False)

    class_id = relationship("Class", foreign_keys=[ClassId])
    subject_id = relationship("Subject", foreign_keys=[SubjectId])
    teacher_id = relationship("Teacher", foreign_keys=[teacherid])


class Assessment(Base):
    __tablename__ = 'assessment'
    __table_args__ = (PrimaryKeyConstraint('studentid', 'subjectid'), {"schema": "school"})

    studentid = Column('studentid', Integer, ForeignKey('school.student.studentid', ondelete="CASCADE"))
    subjectid = Column('subjectid', Integer, ForeignKey('school.subject.subjectid', ondelete="CASCADE"))
    firsttrimester = Column(Integer, nullable=False)
    secondtrimester = Column(Integer, nullable=False)
    thirdtrimester = Column(Integer, nullable=False)
    finalassessment = Column(Numeric, nullable=False)

    student_id = relationship("Student", foreign_keys=[studentid])
    subject_id = relationship("Subject", foreign_keys=[subjectid])


# По названию предмета и дня недели вывести препо который ведет и кол-во обучающихся в соотв группе
