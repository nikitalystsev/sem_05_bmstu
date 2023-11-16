create extension if not exists plpython3u;

-- Триггер CLR
-- Информация о добавленном пациенте
create or replace function info_about_add_patient_func_py()
returns trigger 
language plpython3u
as
$$ 
	plpy.notice('Пациент был успешно добавлен!')
	plpy.notice(f"id = {TD['new']['id']}, name = {TD['new']['fio']}")
$$;

create or replace trigger info_about_add_patient
after insert on patients
for each row 
execute function info_about_add_patient_func_py();

insert into patients (fio, date_of_birth, gender, age, snils, policy_oms, address, phone, empl)
values ('никто', '2003-07-15', 'M', 20, '12345678910121', '1234567891012112', 'планета Земля', '88005553535', true);
