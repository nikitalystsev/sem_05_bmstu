select t1.id, t1.var1, t2.var2, greatest(t1.valid_from_dttm, t2.valid_from_dttm), least(t1.valid_to_dttm, t2.valid_to_dttm)
from table1 as t1
join table2 as t2
on t1.id = t2.id and t1.valid_to_dttm > t2.valid_from_dttm;