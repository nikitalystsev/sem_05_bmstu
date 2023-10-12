-- https://metanit.com/sql/postgresql/2.6.php - можно прочитать про изменение таблиц
-- https://habr.com/ru/articles/194738/ - можно почитать про каскадное удаление данных

ALTER TABLE doctors
ALTER COLUMN id_doc SET DEFAULT uuid_generate_v4(),
ALTER COLUMN fio SET NOT NULL,
ALTER COLUMN age SET NOT NULL,
ADD CHECK (age >= 27 AND age <= 93),
ALTER COLUMN speciality SET NOT NULL,
ALTER COLUMN gender SET NOT NULL,
ALTER COLUMN type_of_financ SET NOT NULL,
ALTER COLUMN employment_date SET NOT NULL,
ALTER COLUMN cabinet SET NOT NULL,
ADD CHECK (cabinet >= 1 AND cabinet <= 1000),
ALTER COLUMN office_mail SET NOT NULL;

ALTER TABLE patients
ALTER COLUMN id_pat SET DEFAULT uuid_generate_v4(),
ALTER COLUMN fio SET NOT NULL, -- мб и одинаковы у нескольких пациентов
ALTER COLUMN date_of_birth SET NOT NULL,
ALTER COLUMN gender SET NOT NULL,
ALTER COLUMN snils SET NOT NULL,
ADD UNIQUE (snils),
ALTER COLUMN policy_oms SET NOT NULL,
ADD UNIQUE (policy_oms),
ALTER COLUMN address_pat SET NOT NULL,
ALTER COLUMN phone_number SET NOT NULL,
ADD UNIQUE (phone_number),
ALTER COLUMN employment SET NOT NULL; 

ALTER TABLE diagnoses
ALTER COLUMN id_dia SET DEFAULT uuid_generate_v4(),
ALTER COLUMN title SET NOT NULL,
ADD UNIQUE (title),
ALTER COLUMN symptoms SET NOT NULL,
ALTER COLUMN risk_group SET NOT NULL,
ALTER COLUMN probability_of_death SET NOT NULL,
ADD CHECK (probability_of_death >= 0 AND probability_of_death <= 100),
ALTER COLUMN is_chronic SET NOT NULL,
ALTER COLUMN probability_of_relapse SET NOT NULL,
ADD CHECK (probability_of_relapse >= 0 AND probability_of_relapse <= 100);

ALTER TABLE wards
ALTER COLUMN id_ward SET DEFAULT uuid_generate_v4(),
ALTER COLUMN num SET NOT NULL,
ADD UNIQUE (num),
ADD CHECK (num >= 100),
ALTER COLUMN type_ward SET NOT NULL,
ALTER COLUMN capacity SET NOT NULL,
ADD CHECK (capacity >= 1 AND capacity <= 10),
ALTER COLUMN is_WC SET NOT NULL,
ALTER COLUMN is_full SET NOT NULL;

ALTER TABLE admissions
ALTER COLUMN id_adm SET DEFAULT uuid_generate_v4(),
ALTER COLUMN id_pat SET NOT NULL,
ADD FOREIGN KEY (id_pat) REFERENCES patients(id_pat) on delete cascade on update cascade,
ALTER COLUMN id_doc SET NOT NULL,
ADD FOREIGN KEY (id_doc) REFERENCES doctors(id_doc) on delete cascade on update cascade,
ALTER COLUMN id_dia SET NOT NULL,
ADD FOREIGN KEY (id_dia) REFERENCES diagnoses(id_dia) on delete cascade on update cascade,
ALTER COLUMN id_ward SET NOT NULL,
ADD FOREIGN KEY (id_ward) REFERENCES wards(id_ward) on delete cascade on update cascade,
ALTER COLUMN date_adm SET NOT NULL,
ALTER COLUMN ambulatory_treatment SET NOT NULL,
ALTER COLUMN term SET NOT NULL,
ADD CHECK (term >= 1 AND term <= 365);
