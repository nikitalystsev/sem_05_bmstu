-- Все пациенты со смешным именем "Олимпиада"

select *
from patients as pat
where pat.fio like 'Олимпиад%';