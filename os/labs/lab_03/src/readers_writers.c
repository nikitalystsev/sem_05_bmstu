#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define COUNT_READERS 5
#define COUNT_WRITERS 3

#define READER_SLEEP_TIME 2
#define WRITER_SLEEP_TIME 2

// семафоры
#define ACTIVE_READERS 0 // Кол-во активных читателей;
#define CAN_READ 1       // Читатель может читать? (есть ли активный писатель)
#define CAN_WRITE 2      // писатель может записать?
#define WAIT_WRITERS 3   // Кол-во ожидающий писателей, которые хотят записать.

// Операции над семафорами:
#define P -1 // Пропустить;
#define V 1  // Освободить.
#define S 0  // sleep.

struct sembuf StartRead[5] = {
    {CAN_READ, V, 0},
    {WAIT_WRITERS, S, 0},   // проверка, если ли ждущие писатели
    {CAN_WRITE, S, 0},      // проверка, что писатель не пишет
    {ACTIVE_READERS, V, 0}, // инкремент активных читателей
    {CAN_READ, P, 0}

};

struct sembuf StopRead[1] = {
    {ACTIVE_READERS, P, 0} // Декремент активных читателей
};

struct sembuf StartWrite[6] = {
    {WAIT_WRITERS, V, 0},   // инкремент счётчика ждущих писателей
    {ACTIVE_READERS, S, 0}, // проверка, есть ли активный читатель
    {CAN_WRITE, S, 0},      // проверка, пишет ли другой писатель
    {CAN_WRITE, V, 0},      // захват семафора активного писателя
    {CAN_READ, V, 0},       // захват семафора может ли читать (то есть запрет чтения)
    {WAIT_WRITERS, P, 0}    // декремент счётчика ждущих писателей
};

struct sembuf StopWrite[2] = {
    {CAN_READ, P, 0}, // Разрешает читать
    {CAN_WRITE, P, 0} // Разрешает писать. освобождение активного писателя
};

int start_read(int sem_id)
{
    return semop(sem_id, StartRead, 5);
}

int stop_read(int sem_id)
{
    return semop(sem_id, StopRead, 1);
}

int start_write(int sem_id)
{
    return semop(sem_id, StartWrite, 6);
}

int stop_write(int sem_id)
{
    return semop(sem_id, StopWrite, 2);
}

void reader(const int semid, const int *addr)
{
    int sleep_time = rand() % READER_SLEEP_TIME + 1;
    sleep(sleep_time);

    int rc = start_read(semid);

    if (rc == -1)
    {
        perror("Ошибка start_read\n");
        exit(EXIT_FAILURE);
    }

    printf("Reader (id = %d) read: %d\n", getpid(), *addr);

    rc = stop_read(semid);

    if (rc == -1)
    {
        perror("Ошибка stop_read\n");
        exit(EXIT_FAILURE);
    }
}

void writer(const int semid, int *addr)
{
    int sleep_time = rand() % WRITER_SLEEP_TIME + 1;
    sleep(sleep_time);

    int rc = start_write(semid);
    if (rc == -1)
    {
        perror("Ошибка start_write\n");
        exit(EXIT_FAILURE);
    }

    (*addr)++;
    printf("Writer (id = %d) write: %d\n", getpid(), *addr);

    rc = stop_write(semid);

    if (rc == -1)
    {
        perror("Ошибка stop_write\n");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    int status;

    // флаги, определяющие права доступа к разделяемой
    // памяти (и семафорам) для всех категорий пользователей
    int perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    // создаем новый сегмент разделяемой памяти с ключом IPC_PRIVATE
    // и получаем его идентификатор
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | perms);

    if (shmid == -1)
    {
        perror("Ошибка shmget\n");
        exit(EXIT_FAILURE);
    }

    // получаем указатель на начало созданного в функции shmget сегмента
    int *addr = shmat(shmid, 0, 0);

    if (addr == (int *)-1)
    {
        perror("Ошибка shmat\n");
        exit(EXIT_FAILURE);
    }

    // создаем набор из 4-х семафоров с ключом 100 (c примера)
    // и получаем его идентификатор
    int semid = semget(IPC_PRIVATE, 4, IPC_CREAT | perms);

    if (semid == -1)
    {
        perror("Ошибка semget\n");
        return -1;
    }

    int rc_can_write = semctl(semid, CAN_WRITE, SETVAL, 0);
    int rc_can_read = semctl(semid, CAN_READ, SETVAL, 0);
    int rc_active_readers = semctl(semid, ACTIVE_READERS, SETVAL, 0);
    int rc_wait_writers = semctl(semid, WAIT_WRITERS, SETVAL, 0);

    if (rc_can_write == -1 || rc_can_read == -1 || rc_active_readers == -1 || rc_wait_writers)
    {
        perror("Ошибка semctl.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < COUNT_READERS; ++i)
    {
        pid_t childpid;
        if ((childpid = fork()) == -1)
        {
            perror("Ошибка fork (readers)\n");
            exit(EXIT_FAILURE);
        }
        else if (childpid == 0)
        {
            while (1)
                reader(semid, addr);
            exit(0);
        }
    }

    for (int i = 0; i < COUNT_WRITERS; ++i)
    {
        pid_t childpid;
        if ((childpid = fork()) == -1)
        {
            perror("Ошибка fork (writers)\n");
            exit(EXIT_FAILURE);
        }
        else if (childpid == 0)
        {
            while (1)
                writer(semid, addr);
            exit(0);
        }
    }

    for (size_t i = 0; i < COUNT_WRITERS + COUNT_WRITERS; ++i)
    {
        pid_t w_pid;
        int status;

        w_pid = wait(&status);

        if (wait(&status) == -1)
            perror("Error with child process.\n");

        if (WIFEXITED(status))
        {
            printf("Child process: PID = %d завершился с кодом %d\n", w_pid, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Child process: PID = %d killed by signal %d\n", w_pid, WTERMSIG(status));
        }
        else if (WIFSTOPPED(status))
        {
            printf("Child process: PID = %d stopped by signal %d\n", w_pid, WSTOPSIG(status));
        }
    }

    // в конце надо почистить семафоры и разделяемую память

    if (shmdt(addr) == -1)
    {
        perror("Ошибка shmdt.\n");
        exit(EXIT_FAILURE);
    }

    // IPC_RMID используется для пометки сегмента как удаленного.
    if (semctl(semid, 1, IPC_RMID, NULL) == -1)
    {
        perror("Can't delete semafor.\n");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("Can't mark a segment as deleted.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}