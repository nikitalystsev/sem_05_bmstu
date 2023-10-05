COPY doctors
FROM '/var/lib/postgres/data/csv/doctors.csv'
DELIMITER ',' CSV;

COPY patients
FROM '/var/lib/postgres/data/csv/patients.csv'
DELIMITER ',' CSV;

COPY diagnoses
FROM '/var/lib/postgres/data/csv/diagnoses.csv'
DELIMITER ',' CSV;

COPY wards
FROM '/var/lib/postgres/data/csv/wards.csv'
DELIMITER ',' CSV;

COPY admissions
FROM '/var/lib/postgres/data/csv/admissions.csv'
DELIMITER ',' CSV;
