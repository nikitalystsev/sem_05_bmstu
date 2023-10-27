-- Инструкция SELECT, использующая вложенные подзапросы с уровнем вложенности 3.
-- получить список докторов, у которых пациенты с хроническим диагнозом лежит в палате, которая заполнена меньше, чем
-- среднее заполнение палат такого типа

select *
from doctors as doc
where doc.id in
(
	select adm.id_doc
	from admissions as adm 
	where adm.id_dia in 
	(
		select dia.id
		from diagnoses as dia
		where dia.is_chronic = true
	) and adm.id_ward in 
	(
		select w.id
		from wards as w
		where w.engaged < 
		(
			select avg(w2.engaged)
			from wards as w2
			where w.type = w2.type
		)
	)
);
