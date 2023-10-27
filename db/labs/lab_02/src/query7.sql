-- Инструкция SELECT, использующая агрегатные функции в выражениях столбцов
-- получить средний заработок докторов в зависимости от должности

select doc.position, round(avg(doc.wage)) as avg_wage
from doctors as doc
group by doc.position
order by avg_wage;
