-- https://metanit.com/sql/postgresql/2.6.php - можно прочитать про изменение таблиц
-- https://habr.com/ru/articles/194738/ - можно почитать про каскадное удаление данных

ALTER TABLE doctors
ALTER COLUMN id SET DEFAULT uuid_generate_v4(),
ALTER COLUMN fio SET NOT NULL,
ALTER COLUMN age SET NOT NULL,
ADD CHECK (age >= 27 AND age <= 93),
ALTER COLUMN gender SET NOT NULL,
ALTER COLUMN position SET NOT NULL,
ALTER COLUMN wage SET NOT NULL,
ALTER COLUMN type_of_financ SET NOT NULL,
ALTER COLUMN empl_date SET NOT NULL,
ALTER COLUMN cabinet SET NOT NULL,
ADD CHECK (cabinet >= 1 AND cabinet <= 1000),
ALTER COLUMN mail SET NOT NULL;

ALTER TABLE patients
ALTER COLUMN id SET DEFAULT uuid_generate_v4(),
ALTER COLUMN fio SET NOT NULL, -- мб и одинаковы у нескольких пациентов
ALTER COLUMN date_of_birth SET NOT NULL,
ALTER COLUMN gender SET NOT NULL,
ALTER COLUMN age SET NOT NULL,
ALTER COLUMN snils SET NOT NULL,
ADD UNIQUE (snils),
ALTER COLUMN policy_oms SET NOT NULL,
ADD UNIQUE (policy_oms),
ALTER COLUMN address SET NOT NULL,
ALTER COLUMN phone SET NOT NULL,
ADD UNIQUE (phone),
ALTER COLUMN empl SET NOT NULL; 

ALTER TABLE diagnoses
ALTER COLUMN id SET DEFAULT uuid_generate_v4(),
ALTER COLUMN name SET NOT NULL,
ADD UNIQUE (name),
ALTER COLUMN symptoms SET NOT NULL,
ALTER COLUMN risk_group SET NOT NULL,
ALTER COLUMN prob_of_death SET NOT NULL,
ADD CHECK (prob_of_death >= 0 AND prob_of_death <= 100),
ALTER COLUMN is_chronic SET NOT NULL,
ALTER COLUMN prob_of_relapse SET NOT NULL,
ADD CHECK (prob_of_relapse >= 0 AND prob_of_relapse <= 100);

ALTER TABLE wards
ALTER COLUMN id SET DEFAULT uuid_generate_v4(),
ALTER COLUMN number SET NOT NULL,
ADD UNIQUE (number),
ADD CHECK (number >= 100),
ALTER COLUMN type SET NOT NULL,
ALTER COLUMN capacity SET NOT NULL,
ADD CHECK (capacity >= 1 AND capacity <= 20),
ALTER COLUMN engaged SET NOT NULL,
ALTER COLUMN is_WC SET NOT NULL,
ALTER COLUMN is_full SET NOT NULL;

ALTER TABLE admissions
ALTER COLUMN id SET DEFAULT uuid_generate_v4(),
ALTER COLUMN id_pat SET NOT NULL,
ADD FOREIGN KEY (id_pat) REFERENCES patients(id) on delete cascade on update cascade,
ALTER COLUMN id_doc SET NOT NULL,
ADD FOREIGN KEY (id_doc) REFERENCES doctors(id) on delete cascade on update cascade,
ALTER COLUMN id_dia SET NOT NULL,
ADD FOREIGN KEY (id_dia) REFERENCES diagnoses(id) on delete cascade on update cascade,
ALTER COLUMN id_ward SET NOT NULL,
ADD FOREIGN KEY (id_ward) REFERENCES wards(id) on delete cascade on update cascade,
ALTER COLUMN date_adm SET NOT NULL,
ALTER COLUMN is_ambul_treatment SET NOT NULL,
ALTER COLUMN term SET NOT NULL,
ADD CHECK (term >= 1 AND term <= 365);
