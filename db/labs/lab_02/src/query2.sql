-- диагнозы с вероятностью смерти от 20 до 100

select *
from diagnoses as dia
where probability_of_death between 20 and 100;