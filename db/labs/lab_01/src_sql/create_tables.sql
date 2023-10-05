CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

CREATE TABLE IF NOT EXISTS doctors (
    id_doc int primary key,
    fio text,
    gender boolean,
    type_of_financ varchar(100),
    academic_degree varchar(100)
);

CREATE TABLE IF NOT EXISTS patients (
    id_pat int primary key,
    fio text,
    date_of_birth date,
    gender boolean,
    address varchar(100),
    phone_number varchar(100)
);

CREATE TABLE IF NOT EXISTS diagnoses (
    id_dia int PRIMARY KEY,
    title varchar(100),
    symptoms text,
    risk_group varchar(100),
    probability_of_death real,
    is_chronic boolean,
    probability_of_relapse real
);

CREATE TABLE IF NOT EXISTS wards (
    id_ward int PRIMARY KEY,
    num int,
    typ varchar(100),
    capacity int,
    is_wc boolean,
    is_full boolean
);

CREATE TABLE IF NOT EXISTS admissions (
    id_adm int PRIMARY KEY,
    id_pac int,
    id_doc int,
    id_dia int,
    id_ward int,
    date_adm date,
    ambulatory_treatment boolean
);
