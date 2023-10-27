-- Рекурсивную хранимую процедуру или хранимую процедур с рекурсивным ОТВ

-- рекурсивная хранимая процедура
-- удалить все предыдущие записи от той, что переданы в качестве параметра
create or replace procedure del_prev_by_adm(in _id_adm UUID)
language plpgsql
as 
$$
	declare 
		_prev UUID;
		
	begin
		select adm.prev_adm into _prev
		from admissions as adm
		where adm.id = _id_adm;

		if _prev is null then
			raise notice 'первое поступление id = %', _id_adm;
		else
			call del_prev_by_adm(_prev);
			delete from admissions 
			where id = _prev;
		end if;
	end
$$;

call del_prev_by_adm('5d3c6326-c4d7-442d-bb5f-91561fc6baf4');

-- -- просмотреть все  предыдущие записи пациента, начиная с переданной в качестве параметра
-- create or replace procedure find_all_adm_by_patient(in _id_adm UUID)
-- language plpgsql
-- as 
-- $$
-- 	declare 
-- 		_prev UUID;
		
-- 	begin
-- 		select adm.prev_adm into _prev
-- 		from admissions as adm
-- 		where adm.id = _id_adm;

-- 		if _prev is null then
-- 			raise notice 'первое поступление id = %', _id_adm;
-- 		else
-- 			call find_all_adm_by_patient(_prev);
-- 			raise notice 'поступление id = %', _id_adm;
-- 		end if;
-- 	end
-- $$;

-- call find_all_adm_by_patient('5d3c6326-c4d7-442d-bb5f-91561fc6baf4');