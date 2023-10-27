-- Инструкция SELECT, использующая предикат LIKE
-- Все пациенты с именем "Олимпиада"

select *
from patients as pat
where pat.fio like 'Олимпиад%';