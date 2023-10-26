-- Многооператорная табличная функция
-- вывести более читаемые записи о поступлениях с диагнозами
-- с вероятностью смерти менее переданного в качестве параметра значения процентов
-- более читаемые - вместо id-шников другие данные

create or replace function best_read_adm_less_death(in _prob_of_death real)
returns table 
(
	_id UUID, 
	fio_pat text, 
	fio_doc text, 
	name_dia text, 
	num_ward int, 
	date_adm date, 
	is_ambul_treatment boolean, 
	term int
)
language plpgsql
as 
$$
	begin
	
	create temp table if not exists best_adm
	(
		_id UUID, 
		fio_pat text, 
		fio_doc text, 
		name_dia text, 
		num_ward int, 
		date_adm date, 
		is_ambul_treatment boolean, 
		term int
	);
	
	insert into best_adm 
	select adm.id, pat.fio, doc.fio, dia.name, w.number, adm.date_adm, adm.is_ambul_treatment, adm.term
	from admissions as adm 
	join patients as pat
	on adm.id_pat = pat.id
	join doctors as doc
	on adm.id_doc = doc.id
	join diagnoses as dia
	on adm.id_dia = dia.id
	join wards as w
	on adm.id_ward = w.id
	where dia.prob_of_death < _prob_of_death;
	
	return query
	(
		select *
		from best_adm
	);
	
	end
$$;

select * 
from best_read_adm_less_death(70);