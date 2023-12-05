#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define COUNT_READERS 5
#define COUNT_WRITERS 3

#define READER_SLEEP_TIME 2
#define WRITER_SLEEP_TIME 2

#define WAITING_READERS 0
#define WAITING_WRITERS 1
#define ACTIVE_READERS 2
#define ACTIVE_WRITER 3
#define BIN 4

// Операции над семафорами:
#define P -1 // Пропустить;
#define V 1  // Освободить.
#define S 0  // Ожидание освобождения без его захвата

int flag = 1; // флаг для обработчика сигнала

void signal_handler(int sig_num)
{
    flag = 0;
    printf("\nProcess (id = %d) перехватил сигнал %d\n", getpid(), sig_num);
}

struct sembuf _start_read[] = {
    {WAITING_READERS, V, 0},
    {ACTIVE_WRITER, S, 0},   // есть ли активный писатель
    {WAITING_WRITERS, S, 0}, // есть ли ждущие писатели
    {ACTIVE_READERS, V, 0},  // инкремент читателей
    {WAITING_READERS, P, 0}};

struct sembuf _stop_read[] = {
    {ACTIVE_READERS, P, 0}}; // декремент читателей

struct sembuf _start_write[] = {
    {WAITING_WRITERS, V, 0},
    {ACTIVE_READERS, S, 0}, // есть ли активные читатели
    {ACTIVE_WRITER, S, 0},  // есть ли активный писатель
    {ACTIVE_WRITER, V, 0},  // active_writer:= true;
    {BIN, P, 0},
    {WAITING_WRITERS, P, 0}};

struct sembuf _stop_write[] = {
    {BIN, V, 0},
    {ACTIVE_WRITER, P, 0}}; // active_writer:= false;

int start_read(int semid)
{
    return semop(semid, _start_read, 5);
}

int stop_read(int semid)
{
    return semop(semid, _stop_read, 1);
}

int start_write(int semid)
{
    return semop(semid, _start_write, 6);
}

int stop_write(int semid)
{
    return semop(semid, _stop_write, 2);
}

void writer(const int semid, int *addr)
{
    while (flag)
    {
        srand(time(NULL)); // абсолютно случайные задержки
        sleep(rand() % 5 + 1);

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

    exit(EXIT_SUCCESS);
}

void reader(const int semid, const int *addr)
{
    while (flag)
    {
        srand(time(NULL)); // абсолютно случайные задержки

        sleep(rand() % 5 + 1);

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

    exit(EXIT_SUCCESS);
}

int main(void)
{
    srand(time(NULL)); // абсолютно случайные задержки

    if (signal(SIGINT, signal_handler) == SIG_ERR)
    {
        perror("Ошибка signal");
        exit(EXIT_FAILURE);
    }

    // флаги, определяющие права доступа к разделяемой
    // памяти (и семафорам) для всех категорий пользователей
    int perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    // создаем новый сегмент разделяемой памяти с ключом 100 (c примера)
    // и получаем его идентификатор
    int shmid = shmget(100, sizeof(int), IPC_CREAT | perms);

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
    int semid = semget(IPC_PRIVATE, 5, IPC_CREAT | perms);

    if (semid == -1)
    {
        perror("Ошибка semget\n");
        return -1;
    }

    int rc = semctl(semid, ACTIVE_WRITER, SETVAL, 0);

    if (rc == -1)
    {
        perror("Ошибка semctl.\n");
        exit(EXIT_FAILURE);
    }

    rc = semctl(semid, ACTIVE_READERS, SETVAL, 0);

    if (rc == -1)
    {
        perror("Ошибка semctl.\n");
        exit(EXIT_FAILURE);
    }

    rc = semctl(semid, WAITING_READERS, SETVAL, 0);

    if (rc == -1)
    {
        perror("Ошибка semctl.\n");
        exit(EXIT_FAILURE);
    }

    rc = semctl(semid, WAITING_WRITERS, SETVAL, 0);

    if (rc == -1)
    {
        perror("Ошибка semctl.\n");
        exit(EXIT_FAILURE);
    }

    rc = semctl(semid, BIN, SETVAL, 1);

    if (rc == -1)
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
            reader(semid, addr);
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
            writer(semid, addr);
        }
    }

    for (size_t i = 0; i < COUNT_READERS + COUNT_WRITERS; ++i)
    {
        pid_t w_pid;
        int status;

        w_pid = wait(&status);

        if (w_pid == -1)
        {
            perror("Ошибка wait");
            exit(EXIT_FAILURE);
        }

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
