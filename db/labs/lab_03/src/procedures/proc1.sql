-- Хранимую процедуру без параметров или с параметрами

-- без параметров
-- увеличение сроков пребывания в больнице на 14 дней (например, из-за карантина)
create or replace procedure update_term()
language plpgsql
as 
$$
	begin
	
	update admissions
	set term = term + 14
	where term <= 351;
	
	end
$$;


-- call update_term();

select term 
from admissions
order by term;


-- c параметрами
-- повысить зарплату всем врачам переданной в качестве параметра должности на 20 процентов от средней зарплате по 
-- этой же должности
create or replace procedure increase_wage_by_position(in _position VARCHAR(100))
language plpgsql
as 
$$
	declare 
		avg_wage real;
	begin
		
		select avg(doc.wage) into avg_wage
		from doctors as doc
		where doc.position = _position;
		
		update doctors
		set wage = round(wage + avg_wage * 0.2)
		where position = _position;
		
	end
$$;

call increase_wage_by_position('Диабетолог');

select doc.fio, doc.position, doc.wage
from doctors as doc
where position = 'Диабетолог'
order by doc.wage;