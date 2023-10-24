-- Инструкция SELECT, использующая простое обобщенное табличное выражение
-- из таблицы с молодыми платными докторами выбрать 5 первых человек с зарплатой, выше средней 

with doc_young_payers as
(
	select adm.id as adm_id, doc.fio, doc.age, doc.wage, doc.position
	from doctors as doc
	join admissions as adm 
	on doc.id = adm.id_doc 
	where doc.age = 27 and doc.type_of_financ = 'платный'
)

select *
from doc_young_payers as dyp
where dyp.wage > 
(
	select avg(dyp2.wage)
	from doc_young_payers as dyp2
)
order by dyp.wage
limit 5;
