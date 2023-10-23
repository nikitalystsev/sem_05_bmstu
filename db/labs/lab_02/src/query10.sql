-- Инструкция SELECT, использующая поисковое выражение CASE
-- подпись к диагнозу исходя из вероятности рецидива

select dia.name, 
	case
		when dia.prob_of_relapse < 10 then 'не вернется'
		when dia.prob_of_relapse >= 10 AND dia.prob_of_relapse <= 50 then 'возможно вернется'
		else 'она вернется снова!'
	end as rel_type
from diagnoses as dia;