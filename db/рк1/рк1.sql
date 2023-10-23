 -- задание 1

create database рк2;

create table department (
	id int primary key,
	name text,
	description text
);

create table teachers (
	id int primary key,
	fio text, 
	degree varchar(100),
	position varchar(100),
	department_id int,
	foreign key (department_id) REFERENCES department (id) on delete cascade
);

create table subject (
	id int primary key,
	name text,
	hours int,
	semester int,
	rating int 
);

create table studies (
	id int primary key,
	teachers_id int,
	subject_id int,
	foreign key (teachers_id) REFERENCES teachers (Id) on delete cascade,
	foreign key (subject_id) REFERENCES subject (Id) on delete cascade
);


insert into department values (1, 'dep1', 'decr1'),
							(2, 'dep2', 'decr2'),
							(3, 'dep3', 'decr3'),
							(4, 'dep4', 'decr4'),
							(5, 'dep5', 'decr5'),
							(6, 'dep6', 'decr6'),
							(7, 'dep7', 'decr7'),
							(8, 'dep8', 'decr8'),
							(9, 'dep9', 'decr9'),
							(10, 'dep10', 'decr10');
							
insert into subject values (1, 'aa', 40, 5, 1),
							(2, 'db', 150, 5, 7),
							(3, 'aecm', 3000, 4, 3),
							(4, 'os', 27, 5, 8),
							(5, 'tw', 15, 5, 4),
							(6, 'инжа', 52, 1, 9),
							(7, 'интегралы', 78, 2, 2),
							(8, 'опи', 3, 2, 5),
							(9, 'си', 300, 3, 6),
							(10, 'питон', 1, 2, 10);
							
insert into teachers values (1, 'fio1', 'degree1', 'препод', 1),
							(2, 'fio2', 'degree2', 'научрук', 3),
							(3, 'fio3', 'degree3', 'препод', 3),
							(4, 'fio4', 'degree4', 'препод', 5),
							(5, 'fio5', 'degree5', 'препод', 8),
							(6, 'fio6', 'degree6', 'препод', 10),
							(7, 'fio7', 'degree7', 'завкаф', 4),
							(8, 'fio8', 'degree8', 'препод', 6),
							(9, 'fio9', 'degree9', 'препод', 2),
							(10, 'fio10', 'degree10', 'препод', 10);

insert into studies values (1, 2, 7),
							(2, 3, 4),
							(3, 6, 1),
							(4, 5, 5),
							(5, 2, 9),
							(6, 10, 7),
							(7, 4, 6),
							(8, 6, 3),
							(9, 2, 1),
							(10, 7, 9);


-- задание 2
-- Запрос проводит оценку часов для этого предмета (поисковое выражение case)
select sbj.id, sbj.hours,
case 
	when hours < 30 then 'мало'
	when hours > 100 then 'много'
	else 'норм нагрузочка'
end hours_valuation
from subject as sbj;

-- запрос с select с уровнем вложенности 3
-- вывести преподов, которые преподают предметы с первого семестра
select *
from teachers as te
where te.id in (
	select st.teachers_id
	from studies as st
	where st.teachers_id = te.id and st.subject_id in (
		select sb.id
		from subject as sb
		where sb.semester = 1
	)
)

-- запрос с group by и having
-- вывести те должности, у которых число преподавателей больше 5
select position, count(*) 
from teachers
group by position
having count(*) > 5;


-- задание 3
create or replace function copy_user_tables(schema_name text, new_schema_name text)
returns void
as
$$
declare
	table_name text;
	begin
    for table_name in (select table_name from information_schema.tables where table_schema = schema_name and table_type = 'BASE TABLE') 
    loop
        execute 'CREATE TABLE ' || new_schema_name || '.' || table_name || ' (LIKE ' || schema_name || '.' || table_name || ' INCLUDING ALL)';
    end loop;
end;
$$ language plpgsql;

select copy_user_tables('public', 'backup_schema');