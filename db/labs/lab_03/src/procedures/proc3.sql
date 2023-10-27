-- Хранимая процедура с курсором
-- Всем поступившим пациентам с определенным диагнозом отменить амбулаторное лечение, если оно было назначено
create or replace procedure cancel_ambul_treat_by_dia(in _id_dia UUID)
language plpgsql
as
$$
	declare 
		_curs no scroll cursor for 
		select *
		from admissions as adm 
		where adm.id_dia = _id_dia and adm.is_ambul_treatment = true;
		_record record;
	begin 
		open _curs;
		
		loop
			fetch next from _curs into _record;
			exit when not found;
			
			update admissions 
			set is_ambul_treatment = false
			where current of _curs;
			
			raise notice 'Отменено амбулаторное лечение для пациента с ID: %', _record.id_pat;
			
		end loop;
		
		close _curs;
	end
$$;

call cancel_ambul_treat_by_dia('883f5dee-1528-4ebf-88a8-f43a8edad964');