-- Инструкция SELECT, консолидирующая данные с помощью предложения GROUP BY, но без предложения HAVING
-- получить те группы риска, у которых средняя вероятность смерти от болезней менее 50 процентов, а также вывести количество диагнозов, которым подвержены эти группы

select dia.risk_group, count(*) as cdia, 
round(avg(dia.prob_of_death)) as avg_death
from diagnoses as dia
group by dia.risk_group
having round(avg(dia.prob_of_death)) < 50;
