-- Создать таблицу, в которой будет атрибут(-ы) с типом XML или JSON, или
-- добавить атрибут с типом XML или JSON к уже существующей таблице.
-- Заполнить атрибут правдоподобными данными с помощью команд INSERT
-- или UPDATE. 

drop table if exists other_table;

create table other_table
(
	other_data json
);

insert into other_table
values 
(
	'{"id":"576ec01c-6c21-4c3a-840b-782c3fef7f1f","fio":"Блинов Тимур Венедиктович","age":63,"gender":"М","position":"Врач функциональной диагностики","wage":183779,"type_of_financ":"бюджет","empl_date":"1975-07-06","cabinet":272,"mail":"ijakusheva@ao.info"}'
),
(
	'{"id":"8e2164d0-d301-412d-b4a5-6704d7efc4a0","fio":"Леон Викентьевич Гущин","age":83,"gender":"М","position":"Малоинвазивный хирург","wage":91793,"type_of_financ":"платный","empl_date":"2022-10-12","cabinet":738,"mail":"dobromisl_00@zao.biz"}'
),
(
	'{"id":"214dcbb4-830d-489e-bce2-c4d58605fa0e","fio":"София Ефимовна Дмитриева","age":81,"gender":"Ж","position":"Специалист по сонографии","wage":137132,"type_of_financ":"бюджет","empl_date":"2003-03-31","cabinet":25,"mail":"teterinvadim@strelkova.net"}'
);

select * 
from other_table;