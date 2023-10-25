-- Оконные функции. Использование конструкций MIN/MAX/AVG OVER()
-- для каждого доктора вывести количество поступлений, среднюю зарплату по его должности, 
-- максимальный и минимальный возраст по должности

select distinct doc.id, doc.fio, doc.position,
count(adm.id) over (partition by doc.id) as count_adm,
avg(doc.wage) over (partition by doc.position) as avg_wage_by_pos,
min(doc.age) over (partition by doc.position) as min_age_by_pos,
max(doc.age) over (partition by doc.position) as min_age_by_pos
from doctors as doc
left join admissions as adm
on doc.id = adm.id_doc;
