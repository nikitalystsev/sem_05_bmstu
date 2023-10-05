COPY doctors
FROM '/var/lib/postgres/data/csv/doctors.csv'
DELIMITER ',' CSV;
