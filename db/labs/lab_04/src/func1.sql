-- Определяемая пользователем скалярная функция CLR
-- Скалярная функция, считающая сколько осталось свободных мест в палате

create or replace function get_count_beds_available(in _capacity int, in _engaged int)
returns int
language plpython3u
as 
$$
	return _capacity - _engaged
$$;

select w.number, w.capacity, w.engaged, get_count_beds_available(w.capacity, w.engaged) as count_available
from wards as w;
