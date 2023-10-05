CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

CREATE TABLE doctors (
    id_doc UUID PRIMARY KEY,
    fio text,
    age int,
    speciality varchar(100),
    gender char,
    type_of_financ varchar(10),
    employment_date date,
    cabinet int,
    office_mail varchar(150)
);

CREATE TABLE patients (
    id_pat UUID PRIMARY KEY,
    fio text,
    date_of_birth date,
    gender char,
    snils varchar(14),
    policy_oms varchar(16),
    address_pat text,
    phone_number varchar(20),
    employment boolean -- занятость
);

CREATE TABLE diagnoses (
    id_dia UUID PRIMARY KEY,
    title varchar(100),
    symptoms text,
    risk_group varchar(100),
    probability_of_death real,
    is_chronic boolean,
    probability_of_relapse real
);

CREATE TABLE wards (
    id_ward UUID PRIMARY KEY,
    num int,
    type_ward varchar(30),
    capacity int,
    is_WC boolean,
    is_full boolean
);

CREATE TABLE admissions (
    id_adm UUID PRIMARY KEY,
    id_pat UUID,
    id_doc UUID,
    id_dia UUID,
    id_ward UUID,
    date_adm date,
    ambulatory_treatment boolean,
    term int, 
    prev_adm UUID REFERENCES admissions(id_adm)
);
