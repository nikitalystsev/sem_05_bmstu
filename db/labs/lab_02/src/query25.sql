-- Оконные функции для устранения дублей

with dupl as
( 
	select *
	from admissions
	
	union all
	
	select *
	from admissions
), del_dupl as
(
	select d.id, 
		row_number() over (partition by d.id) as row_num
	from dupl as d
)

select *
from del_dupl
where row_num = 1;