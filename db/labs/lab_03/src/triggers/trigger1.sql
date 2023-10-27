-- Триггер AFTER

create or replace function info_about_add_doctor_func()
returns trigger 
language plpgsql
as
$$ 
	begin 
		raise notice 'Доктор был успешно добавлен!';
    	raise notice 'id = %, name = %, position = %', new.id, new.fio, new.position;
		return new;
	end
$$;

create or replace trigger info_about_add_doctor
after insert on doctors
for each row 
execute function info_about_add_doctor_func();

insert into doctors (fio, age, gender, position, wage, type_of_financ, empl_date, cabinet, mail)
values ('10 доктор', 56, 'M', 'Хирург', '76000', 'бюджет', '2015-12-12', 116, 'doctorwho@galifrey.tl');
