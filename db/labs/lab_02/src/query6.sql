-- Инструкция SELECT, использующая предикат сравнения с квантором.
-- получить список диагнозов, у которых вероятность рецидива меньше, чем у всех хронических диагнозов

select *
from diagnoses as dia
where dia.prob_of_relapse < all
(
	select dia2.prob_of_relapse
    from diagnoses  as dia2
    where dia2.is_chronic = true
);