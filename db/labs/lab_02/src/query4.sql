-- получить список записей с хроническими диагнозами
	
select * 
from admissions as adm
where id_dia in (
	select id_dia
	from diagnoses
	where is_chronic = true
);