 -- Инструкция UPDATE со скалярным подзапросом в предложении SET
 -- установить зарплату невролога в качестве средней для всей больницы
update doctors
set wage = 
(
	select avg(wage)
	from doctors
)
where position = 'Невролог';

select *
from doctors as doc
where doc.position = 'Невролог';