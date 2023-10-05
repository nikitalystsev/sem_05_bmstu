CREATE DATABASE hospital;

CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

CREATE TABLE IF NOT EXISTS doctors (
    id_doc UUID primary key,
    fio text,
    speciality varchar(100),
    gender varchar(2),
    type_of_financ varchar(100)
);

CREATE TABLE IF NOT EXISTS patients (
    id_pat UUID primary key,
    fio text,
    date_of_birth date,
    gender varchar(2),
    address varchar(100),
    phone_number varchar(100)
);

CREATE TABLE IF NOT EXISTS diagnoses (
    id_dia UUID PRIMARY KEY,
    title varchar(100),
    symptoms text,
    risk_group varchar(100),
    probability_of_death real,
    is_chronic boolean,
    probability_of_relapse real
);

CREATE TABLE IF NOT EXISTS wards (
    id_ward UUID PRIMARY KEY,
    num int,
    type_ward varchar(100),
    capacity int,
    is_wc boolean,
    is_full boolean
);

CREATE TABLE IF NOT EXISTS admissions (
    id_adm UUID PRIMARY KEY,
    id_pac UUID,
    id_doc UUID,
    id_dia UUID,
    id_ward UUID,
    date_adm date,
    ambulatory_treatment boolean
);
