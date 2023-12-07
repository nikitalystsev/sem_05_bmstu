-- Выполнить загрузку и сохранение XML или JSON файла в таблицу.
-- Созданная таблица после всех манипуляций должна соответствовать таблице
-- базы данных, созданной в первой лабораторной работе.


drop table if exists doctors_json;
create table doctors_json
(
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

DROP TABLE doctors_json_tmp;

CREATE TEMPORARY TABLE doctors_json_tmp 
(
	json_data json
);

COPY doctors_json_tmp FROM '/var/lib/postgres/data/doctors.json';

INSERT INTO doctors_json
SELECT 
(json_data->>'id')::uuid, 
json_data->>'fio', 
(json_data->>'age')::int, 
json_data->>'gender', 
json_data->>'position', 
(json_data->>'wage')::int, 
json_data->>'type_of_financ', 
(json_data->>'empl_date')::date, 
(json_data->>'cabinet')::int, 
json_data->>'mail' 
FROM doctors_json_tmp;

DROP TABLE doctors_json_tmp;

select * 
from doctors_json;