create database rk3;

create table employees
(
	_id int primary key,
	_fio text,
	_date_of_birth date,
	_department text
);

create table accounting
(
	_id int,
	_date date,
	_day_week varchar(15),
	_time time,
	_is_came int
);

ALTER TABLE accounting
ADD FOREIGN KEY (_id) REFERENCES employees(_id) on delete cascade on update cascade;

insert into employees 
values (1, 'Иванов Иван Иванович', '25-09-1990', 'ИТ'),
	   (2, 'Петров Петр Петрович', '12-11-1987', 'Бухгалтерия');


insert into accounting 
values (1, '19-12-2023', 'Вторник', '9:00:00', 1),
	   (1, '19-12-2023', 'Вторник', '9:20:00', 2),
	   (1, '19-12-2023', 'Вторник', '9:25:00', 1),
	   (2, '19-12-2023', 'Вторник', '9:05:00', 1);

create or replace function get_absent_employees(today_date date)
returns table
(
    employee_id INT,
    employee_name TEXT,
    date_of_birth DATE,
    department TEXT
) 
language plpgsql
as
$$
	begin
		return query
		select
			e._id AS employee_id,
			e._fio AS employee_name,
			e._date_of_birth AS date_of_birth,
			e._department AS department
		from employees as e
		left join accounting as a ON e._id = a._id and a._date = today_date
		where a._id IS NULL;
	end;
$$;

