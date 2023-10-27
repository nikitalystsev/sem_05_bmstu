-- Триггер INSTEAD OF

CREATE OR REPLACE FUNCTION CalculatePatientAge()
RETURNS TRIGGER AS $$
BEGIN
    -- Вычисляем возраст пациента на основе указанной даты рождения
    NEW.age := DATE_PART('year', current_date) - DATE_PART('year', NEW.date_of_birth);
    
	raise notice 'Возраст был успешно посчитан!';
	
	insert into patients(fio, date_of_birth, gender, age, snils, policy_oms, address, phone, empl)
	values (new.fio, new.date_of_birth, new.gender, new.age, new.snils, new.policy_oms, new.address, new.phone, new.empl);
	
	raise notice 'Вставка была выполнена успешно!';
	
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE VIEW patients_view
AS
SELECT *
FROM patients;

CREATE TRIGGER InsteadOfInsertPatient
INSTEAD OF INSERT ON patients_view
FOR EACH ROW
EXECUTE FUNCTION CalculatePatientAge();

	
insert into patients_view (fio, date_of_birth, gender, age, snils, policy_oms, address, phone, empl)
values ('Роза Марион Тайлер', '1986-04-27', 'Ж', 300000, '123-456-789-01', '1234567890123456', '48 Lydstep Flats, Lydstep Crescent, Cardiff CF14 2QU, UK', '89208036272', true);


