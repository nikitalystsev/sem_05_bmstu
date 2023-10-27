-- Хранимая процедура с курсором
-- найти всех пациентов, которые страдают от хронических заболеваний и отсортировать их по риску смерти

CREATE OR REPLACE PROCEDURE find_patients_with_chronic_diagnoses_and_sort()
LANGUAGE plpgsql
AS $$
DECLARE
    patient_cursor CURSOR FOR
        -- Здесь вставьте ранее созданный запрос
        SELECT p.fio AS patient_name, d.name AS diagnosis_name, d.prob_of_death AS death_probability
        FROM patients p
        JOIN admissions a ON p.id = a.id_pat
        JOIN diagnoses d ON a.id_dia = d.id
        WHERE d.is_chronic = TRUE
        ORDER BY d.prob_of_death;

    patient_record RECORD;

BEGIN
    -- Открываем курсор
    OPEN patient_cursor;

    -- Выводим результаты с помощью цикла
    FOR patient_record IN patient_cursor
    LOOP
        RAISE NOTICE 'Patient Name: %, Diagnosis: %, Death Probability: %',
            patient_record.patient_name, patient_record.diagnosis_name, patient_record.death_probability;
    END LOOP;

    -- Закрываем курсор
    CLOSE patient_cursor;
END;
$$;

CALL find_patients_with_chronic_diagnoses_and_sort();