-- Инструкция SELECT, использующая простое выражение CASE
-- тип палаты по количеству вмещаемых пациентов

select w.type, 
	case w.capacity
		when 1 then 'одноместная'
		when 2 then 'двухместная'
		else 'многоместная'
	end cap_type
from wards as w;