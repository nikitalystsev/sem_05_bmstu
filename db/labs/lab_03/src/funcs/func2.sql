-- Подставляемая табличная функция
-- Функция возвращает список имен всех пациентов, которые находятся в определенной палате

create or replace function list_patients_by_ward(in _number int)
returns setof text
language plpgsql
as
$$ 
	begin
	
	return query
	(
		select pat.fio
		from patients as pat
		join admissions as adm
		on pat.id = adm.id_pat
		join wards as w
		on adm.id_ward = w.id
		where w.number = _number
	);
	
	end
$$;

select *
from list_patients_by_ward(4797);