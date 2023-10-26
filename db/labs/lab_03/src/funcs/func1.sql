-- Скалярная функция
--  Функция которая находит количество пациентов, обслуживаемых конкретным врачом (по переданному id в качестве параметра)

create or replace function count_patients_by_doc(_id UUID)
returns int
language plpgsql
as 
$$
	declare
		count_patients int;
		
	begin 
		select count(*) into count_patients
		from patients as pat
		where pat.id in 
		(
			select adm.id_pat
			from admissions as adm
			where pat.id = adm.id_pat and adm.id_doc = _id
		);
		
		return count_patients;
	end
$$;

select count_patients_by_doc('02bc8b61-b4eb-4227-adf1-031ce04d8a6d'); -- 3