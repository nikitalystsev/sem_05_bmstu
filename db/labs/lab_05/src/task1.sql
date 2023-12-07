-- Из таблиц базы данных, созданной в первой лабораторной работе, извлечь
-- данные в XML (MSSQL) или JSON(Oracle, Postgres). Для выгрузки в XML
-- проверить все режимы конструкции FOR XML

-- sudo chown postgres:postgres <имя файла>.json - смена владельца файла на postgres
-- по другому не зааписывает, почему то

-- копируем все admissions в json файл
copy 
(
	select row_to_json(adm) 
	from admissions as adm 
) 
to '/var/lib/postgres/data/admissions.json';

copy 
(
	select row_to_json(doc) 
	from doctors as doc
) 
to '/var/lib/postgres/data/doctors.json';

copy 
(
	select row_to_json(pat) 
	from patients as pat
) 
to '/var/lib/postgres/data/patients.json';

copy 
(
	select row_to_json(dia) 
	from diagnoses as dia
) 
to '/var/lib/postgres/data/diagnoses.json';

copy 
(
	select row_to_json(w) 
	from wards as w
) 
to '/var/lib/postgres/data/wards.json';