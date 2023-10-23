CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

CREATE TABLE doctors (
    id UUID PRIMARY KEY,
    fio text,
    age int,
    gender char,
    position varchar(100),
    wage int, -- зарплата
    type_of_financ varchar(10),
    empl_date date,
    cabinet int,
    mail varchar(150)
);

CREATE TABLE patients (
    id UUID PRIMARY KEY,
    fio text,
    date_of_birth date,
    gender char,
    age int,
    snils varchar(14),
    policy_oms varchar(16),
    address text,
    phone varchar(20),
    empl boolean -- занятость
);

CREATE TABLE diagnoses (
    id UUID PRIMARY KEY,
    name varchar(100),
    symptoms text,
    risk_group varchar(100),
    prob_of_death real,
    is_chronic boolean,
    prob_of_relapse real
);

CREATE TABLE wards (
    id UUID PRIMARY KEY,
    number int,
    type varchar(30),
    capacity int,
    engaged int, -- сколько занято мест
    is_WC boolean,
    is_full boolean
);

CREATE TABLE admissions (
    id UUID PRIMARY KEY,
    id_pat UUID,
    id_doc UUID,
    id_dia UUID,
    id_ward UUID,
    date_adm date,
    is_ambul_treatment boolean,
    term int, 
    prev_adm UUID REFERENCES admissions(id)
);
