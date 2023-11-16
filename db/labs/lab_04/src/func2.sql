create extension if not exists plpython3u;

-- Пользовательская агрегатная функция CLR
-- Функция вернет количество врачей, работающих по переданной в качестве параметра должности

create or replace function get_count_doctors_by_position(in _position text)
returns int
language plpython3u
as 
$$
	_count = 0

	for _row in plpy.cursor("select doc.position from doctors as doc"):
		if _row['position'] == _position:
			_count += 1

	return _count
$$;

select get_count_doctors_by_position('Гинеколог');