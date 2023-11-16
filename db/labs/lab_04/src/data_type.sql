create extension if not exists plpython3u;

-- Определяемый пользователем тип данных CLR
-- create type death_chronic_diagnoses AS (
-- 	name varchar(100),
-- 	prob_of_death real,
-- 	is_chronic boolean
-- );


create or replace function get_death_chronic_diagnoses()
returns setof death_chronic_diagnoses
language plpython3u
as 
$$
	rv = plpy.execute(
		"""
		select name, prob_of_death, is_chronic
		from diagnoses 
		where prob_of_death >= 95
		"""
	)
	

	return rv
$$;

select *
from get_death_chronic_diagnoses();