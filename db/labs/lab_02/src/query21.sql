-- Инструкция DELETE с вложенным коррелированным подзапросом в предложении WHERE
-- удалить все записи с диагнозами с группой риска беременные и с вероятностью смерти менее 50 процентов

delete from admissions 
where id_dia in 
(
	select adm.id_dia
	from admissions as adm 
	join diagnoses as dia
	on dia.id = adm.id_dia
	where dia.risk_group = 'Беременные' and dia.prob_of_death < 50
);

select *
from admissions;