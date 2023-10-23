-- select, использующий агрегатные функции в выражениях столбцов
-- получить все заполненные палаты

select count(*)
from wards as w
where w.is_full = true;