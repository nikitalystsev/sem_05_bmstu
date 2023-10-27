-- . Инструкция SELECT, использующая предикат BETWEEN
-- вывести диагнозы с вероятностью смерти от 20 до 100 процентов

select *
from diagnoses as dia
where dia.prob_of_death between 20 and 100;
