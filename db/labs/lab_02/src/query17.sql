-- Многострочная инструкция INSERT, выполняющая вставку в таблицу результирующего набора данных вложенного подзапроса
-- добавить записи с диагнозами с вероятностью рецидива меньше 1 процента и не хронические, а также занятые пациенты

insert into admissions (id_pat, id_doc, id_dia, id_ward, date_adm, is_ambul_treatment, term)
select adm.id_pat, adm.id_doc, adm.id_dia, adm.id_ward, adm.date_adm, adm.is_ambul_treatment, adm.term
from admissions as adm
where adm.id_dia in 
(
	select dia.id
	from diagnoses as dia
	where dia.prob_of_relapse < 1 and dia.is_chronic = false
) and adm.id_pat in
(
	select pat.id
	from patients as pat
	where pat.empl = true
);