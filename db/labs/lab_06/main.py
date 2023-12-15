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


if __name__ == "__main__":
    main()
