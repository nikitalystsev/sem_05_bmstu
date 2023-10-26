-- Рекурсивную функцию или функцию с рекурсивным ОТВ
-- вывести список пациентов, которые попали в больницу _depth и более раз

create or replace function list_patients_by_depth_adm(in _depth int)
returns table 
(
	id UUID,
    fio text,
    date_of_birth date,
    gender char,
    age int,
    snils varchar(14),
    policy_oms varchar(16),
    address text,
    phone varchar(20),
    empl boolean 
)
language plpgsql
as
$$
	begin 
	
	return query
	(
		with recursive adm_by_depth(id, prev_adm, id_pat, depth) as
		(
			-- нерекурсивная часть
			select adm.id, adm.prev_adm, adm.id_pat, 0 as depth
			from admissions as adm
			where adm.prev_adm is null

			union all 

			-- рекурсивная часть
			select adm.id, adm.prev_adm, adm.id_pat, depth + 1
			from admissions as adm
			join adm_by_depth as abd
			on adm.prev_adm = abd.id
		)
		
		select pat.*
		from adm_by_depth as abd
		join patients as pat
		on abd.id_pat = pat.id
		where depth = _depth
	);
	
	end
$$;

select * 
from list_patients_by_depth_adm(2);