-- Создание новой временной локальной таблицы из результирующего набора данных инструкции SELECT
-- получить табличку записей, содержащей только хронические диагнозы

drop table if exists adm_chron;

select *
into temp adm_chron
from admissions as adm
where adm.id_dia in 
(
	select dia.id
	from diagnoses as dia
	where dia.id = adm.id_dia and dia.is_chronic = true
);

select * 
from adm_chron;