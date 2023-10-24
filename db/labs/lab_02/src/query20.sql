-- Простая инструкция DELETE
-- удалить неактуальные записи с прошлого столетия

delete from admissions
where date_adm < '2000-01-01';

select * 
from admissions as adm;