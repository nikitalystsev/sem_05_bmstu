-- Простая инструкция UPDATE
-- поднять зарплату вирусологам

-- до поднятия
select doc.fio, doc.wage
from doctors as doc 
where doc.position = 'Вирусолог';


update doctors 
set wage = wage * 2
where doc.position = 'Вирусолог';

-- после поднятия
select doc.fio, doc.wage
from doctors as doc 
where doc.position = 'Вирусолог';