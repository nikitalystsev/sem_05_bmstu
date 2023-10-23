-- Инструкция SELECT, консолидирующая данные с помощью предложения GROUP BY, но без предложения HAVING
-- получить для каждой группы риска получить количество диагнозов, которым они подвержены, средние вероятности смерти и вероятности рецидива

select dia.risk_group, count(*) as cdia, round(avg(dia.prob_of_death)) avg_death, round(avg(dia.prob_of_relapse)) as avg_relapse
from diagnoses as dia
group by dia.risk_group;