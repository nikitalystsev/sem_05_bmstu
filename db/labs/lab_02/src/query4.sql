-- select, использующий предикат in с вложенным подзапросом
-- получить список записей с хроническими диагнозами
	
select * 
from admissions as adm
where adm.id_dia in (
	select dia.id
	from diagnoses as dia
	where dia.is_chronic = true
);