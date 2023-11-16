create extension if not exists plpython3u;

-- Определяемая пользователем табличная функция CLR
-- Функция выводит более читаемые записи о поступлениях с диагнозами
-- с вероятностью смерти менее переданного в качестве параметра значения процентов
-- более читаемые - вместо id-шников другие данные
create or replace function best_read_adm_less_death_py(in _prob_of_death real)
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
language plpython3u
as 
$$
	rv = plpy.execute(
		"""
		select adm.id as _id, pat.fio as fio_pat, doc.fio as fio_doc, dia.name as name_dia, w.number as num_ward, adm.date_adm, adm.is_ambul_treatment, adm.term, dia.prob_of_death as prob_of_death
		from admissions as adm 
		join patients as pat
		on adm.id_pat = pat.id
		join doctors as doc
		on adm.id_doc = doc.id
		join diagnoses as dia
		on adm.id_dia = dia.id
		join wards as w
		on adm.id_ward = w.id
		"""
	)
	
	res_table = []
	
	for _row in rv:
		if _row['prob_of_death'] < _prob_of_death:
			res_table.append(_row)
			
	return res_table
$$;

select * 
from best_read_adm_less_death_py(40);