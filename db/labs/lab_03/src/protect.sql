-- FUNCTION: public.add_patient_in_admissions()

-- DROP FUNCTION IF EXISTS public.add_patient_in_admissions();
-- При добавлении пациента на основе его диагноза выбрать доктора, у которого больше всего пациентов с таким же 
-- диагнозом, и закрепить этого доктора за добавляемым пациентом

CREATE OR REPLACE FUNCTION public.add_patient_in_admissions()
    RETURNS trigger
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE NOT LEAKPROOF
AS $BODY$
	declare 
		_id_doc UUID;
	begin 
	
	with cnt_doc_by_dia as
    (
        select count(*) as cnt, adm.id_doc
        from admissions as adm 
        where adm.id_dia = new.id_dia
        group by adm.id_doc
    )

    select _cnt.id_doc into _id_doc
    from cnt_doc_by_dia as _cnt
    where _cnt.cnt = 
    (
        select max(_cnt2.cnt)
        from cnt_doc_by_dia as _cnt2
    )
    limit 1;
	
	insert into admissions (id_pat , id_doc,  id_dia , id_ward , date_adm , is_ambul_treatment, term)
	values (new.id_pat, _id_doc, new.id_dia, new.id_ward, new.date_adm, new.is_ambul_treatment, new.term);

	raise notice 'Вставка была выполнена успешно!';
	
	return new;
    
	end
$BODY$;

ALTER FUNCTION public.add_patient_in_admissions()
    OWNER TO nikitalystsev;
