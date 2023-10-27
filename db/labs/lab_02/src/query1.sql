-- Инструкция SELECT, использующая предикат сравнения
-- вывести записи с неврологами, которые старше 35 лет

select adm.id, adm.id_doc, doc.position, doc.age, adm.date_adm, adm.is_ambul_treatment, adm.term
from admissions as adm
join doctors as doc on doc.id = adm.id_doc
where doc.position = 'Невролог' and doc.age > 35
order by doc.age;
