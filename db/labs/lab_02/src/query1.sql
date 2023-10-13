-- записи с неврологами, которые старше 35 лет

select adm.id_doc, doc.speciality, doc.age, adm.date_adm, adm.ambulatory_treatment, adm.term
from admissions as adm
join doctors as doc on doc.id_doc = adm.id_doc
where doc.speciality = 'Невролог' and doc.age >= 35
order by doc.age;