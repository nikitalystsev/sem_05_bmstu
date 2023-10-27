-- Хранимая процедура доступа к метаданным
-- процедуру, которая находит и выводит информацию о всех столбцах во всех таблицах в указанной схеме, 
-- включая их имя, тип данных и максимальную длину (если это текстовые столбцы)

CREATE OR REPLACE PROCEDURE GetColumnMetadataInSchema(schema_name TEXT) AS $$
DECLARE
    _table_name TEXT;
    column_info RECORD;
BEGIN
    FOR _table_name IN (SELECT table_name FROM information_schema.tables WHERE table_schema = schema_name AND table_type = 'BASE TABLE')
    LOOP
        FOR column_info IN (SELECT column_name, data_type, character_maximum_length
                            FROM information_schema.columns
                            WHERE table_name = _table_name)
        LOOP
            RAISE NOTICE 'Таблица: %, Столбец: %, Тип данных: %, Макс. длина: %',
                         _table_name, column_info.column_name, column_info.data_type, column_info.character_maximum_length ;
        END LOOP;
    END LOOP;
END;
$$ LANGUAGE plpgsql;

CALL GetColumnMetadataInSchema('public');