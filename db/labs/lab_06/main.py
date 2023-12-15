from config import host, user, password, db_name
from hospital_db import HospitalDB


def main() -> None:
    """
    Главная функция
    """
    hospital_db = HospitalDB(
        host=host,
        user=user,
        password=password,
        db_name=db_name
    )

    # hospital_db.scalar_query()
    # hospital_db.with_several_join_query()
    # hospital_db.cte_row_number_query()
    # hospital_db.metadata_query()
    # hospital_db.call_scalar_func_query()
    # hospital_db.call_multi_statement_or_table_query()
    # hospital_db.call_stored_procedure_query()
    # hospital_db.call_system_procedure_query()
    # hospital_db.create_table_query()
    # hospital_db.insert_medicines_query()


if __name__ == "__main__":
    main()
