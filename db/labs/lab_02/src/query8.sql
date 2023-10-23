-- Инструкция SELECT, использующая скалярные подзапросы в выражениях столбцов.
-- для каждого доктора получить максимальный срок наблюдения за пациентом

select doc.fio,
(
	select max(adm.term)
	from admissions as adm
	where adm.id_doc = doc.id
) as max_term 
from doctors as doc;