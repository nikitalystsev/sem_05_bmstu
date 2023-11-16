create extension if not exists plpython3u;

-- Хранимая процедура CLR
-- Процедура повышения зарплаты всем врачам переданной в качестве параметра должности на 20 процентов 
create or replace procedure increase_wage_by_position_py(in _position VARCHAR(100))
language plpython3u
as 
$$
	plan = plpy.prepare(
		"""
		update doctors
		set wage = round(wage + wage * 0.2)
		where position = $1;
		""", ["VARCHAR(100)"]
	)
	
	plpy.execute(plan, [_position])
$$;

call increase_wage_by_position_py('Невролог');

select doc.fio, doc.position, doc.wage
from doctors as doc
where position = 'Невролог'
order by doc.wage;