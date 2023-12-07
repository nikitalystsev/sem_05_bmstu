-- Выполнить следующие действия:
-- 1. Извлечь XML/JSON фрагмент из XML/JSON документа

select ot.other_data
from other_table as ot
limit 1;

-- 2. Извлечь значения конкретных узлов или атрибутов XML/JSON
-- документа

select ot.other_data->'id', ot.other_data->'fio'
from other_table as ot;

-- 3. Выполнить проверку существования узла или атрибута

create or replace function insert_if_exists()
returns trigger
language plpgsql
as
$$
	declare
		_key VARCHAR(255);
		_json_value text;
		_is_null INT DEFAULT 0;
	begin
		-- Loop through each key in the JSON object
		for _key in (select json_object_keys(new.other_data))
		loop
			-- Get the value for the current key
			_json_value := new.other_data->>_key;

			-- Check if the value is NULL
			if _json_value is null then
				_is_null := 1;
				exit; -- Exit the loop if any value is NULL
			end if;
		end loop;

		-- Insert the row into the table if all values are not NULL
		if _is_null = 0 then
			raise notice 'Вставка была выполнена успешно!';
			insert into other_table 
			values (new.other_data);
			return new;
		else
			raise notice 'Есть нулевые значения!';
			return null; -- Don't insert the original row
		end if;
	end;
$$;

drop view if exists other_table_view;

create view other_table_view
as
select *
from other_table;

create trigger insert_if_exists_trigger
instead of insert on other_table_view
for each row
execute function insert_if_exists();


insert into  other_table_view 
values
(
    '{"id":"c37ae80a-4f6e-4867-9c9a-771c78055a7d","fio": null,"age":55,"gender":"Ж","position":"Стоматолог","wage":61133,"type_of_financ":"платный","empl_date":"1978-01-06","cabinet":573,"mail":"komissarovauljana@maksidom.org"}'
);

select * 
from other_table;


-- 4. Изменить XML/JSON документ

UPDATE other_table
SET other_data = '{"id":"15f7421e-bb53-4700-a5b3-c3365a05e6c7","fio":"Евдокимова Агафья Захаровна","age":76,"gender":"Ж","position":"Венеролог","wage":151196,"type_of_financ":"бюджет","empl_date":"1976-12-07","cabinet":925,"mail":"galaktion83@rosteh.com"}
';

select * 
from other_table;

-- 5. Разделить XML/JSON документ на несколько строк по узлам

SELECT json_each_text(other_data)
FROM other_table;