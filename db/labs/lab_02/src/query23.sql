-- Инструкция SELECT, использующая рекурсивное обобщенное табличное выражение
-- вывести список пациентов, которые поступили в больницу второй раз

with recursive sec_adm(id, prev_adm, id_pat, depth) as
(
	-- нерекурсивная часть
	select adm.id, adm.prev_adm, adm.id_pat, 0 as depth
	from admissions as adm
	where adm.prev_adm is null
	
	union all 
	
	-- рекурсивная часть
	select adm.id, adm.prev_adm, adm.id_pat, depth + 1
	from admissions as adm
	join sec_adm as sadm
	on adm.prev_adm = sadm.id
)

select sadm.id, sadm.prev_adm, pat.id, pat.fio
from sec_adm as sadm
join patients as pat
on sadm.id_pat = pat.id
where depth = 2;