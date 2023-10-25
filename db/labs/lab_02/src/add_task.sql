with dates_from as
(
  select id, valid_from_dttm from Table1
  union
  select id, valid_to_dttm + interval '1 day' from Table1
  union
  select id, valid_from_dttm from Table2
  union
  select id, valid_to_dttm + interval '1 day' from Table2
), dates_to as
(
  select id, valid_to_dttm from Table1
  union
  select id, valid_from_dttm - interval '1 day' from Table1
  union
  select id, valid_to_dttm from Table2
  union
  select id, valid_from_dttm - interval '1 day' from Table2
), ranges as (
  select df.id, valid_from_dttm, min(valid_to_dttm) as valid_to_dttm
  from dates_from  as df
  join dates_to as dt on dt.id = df.id and dt.valid_to_dttm > df.valid_from_dttm
  group by df.id, valid_from_dttm
  order by valid_from_dttm
)

select rg.id, var1, var2, date(rg.valid_from_dttm) , date(rg.valid_to_dttm)
from ranges as rg
left join table1 as t1 on rg.id = t1.id and rg.valid_from_dttm <= t1.valid_to_dttm and rg.valid_to_dttm >= t1.valid_from_dttm
left join table2 as t2 on rg.id = t2.id and rg.valid_from_dttm <= t2.valid_to_dttm and rg.valid_to_dttm >= t2.valid_from_dttm
order by rg.valid_from_dttm;

