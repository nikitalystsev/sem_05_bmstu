-- select, использующий предикат exists с вложенным подзапросом
-- Найти всех врачей, у которых есть хотя бы один пациент с хроническим диагнозом

select *
from doctors as doc
where exists (
	select *
	from admissions as adm
	join patients as pat
	on adm.id_pat = pat.id
	join diagnoses as dia
	on adm.id_dia = dia.id
	where dia.is_chronic = true and doc.id = adm.id_doc
);