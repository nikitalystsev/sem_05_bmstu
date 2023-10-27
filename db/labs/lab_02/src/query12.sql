-- Инструкция SELECT, использующая вложенные коррелированные подзапросы в качестве производных таблиц в предложении FROM
-- вывести все записи, где самый молодой доктор с бюджетным типом финансирования лечит болезнь с вероятностью рецидива более 60 процентов

select adm.id as adm_id, young_doc.id as doc_id, young_doc.fio as doc_fio, young_doc.age as doc_age, dia_chron.is_chronic as dia_chron
from admissions as adm
join 
(
	select doc.id, doc.fio, doc.age 
	from doctors as doc 
	where doc.age = 27 and doc.type_of_financ = 'бюджет'
) as young_doc 
on adm.id_doc = young_doc.id
join
(
	select dia.id, dia.is_chronic
	from diagnoses as dia
	where dia.is_chronic = true and dia.prob_of_relapse > 60
) as dia_chron
on adm.id_dia = dia_chron.id;