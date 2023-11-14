#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

#define COUNT_PROD 3 // количество производителей (producers)
#define COUNT_CONS 3 // количество потребителей (consumers)

#define BUFFER_SIZE 1024 // размер буфера в задаче производство потребления

#define SB 0 // индекс бинарного семафора
#define SE 1 // индекс считающего семафора, содержащего количество пустых ячеек в буфере
#define SF 2 // индекс считающего семафора, содержащего количество занятых ячеек в буфере

#define P -1
#define V 1

int flag = 1; // флаг для обработчика сигнала

void signal_handler(int sig_num)
{
    flag = 0;
    printf("\nПойман обработчик %d\n", sig_num);
}

struct sembuf producers_begin[2] = {
    {SE, P, 0},
    {SB, P, 0}};
struct sembuf producers_end[2] = {
    {SB, V, 0},
    {SF, V, 0}};

struct sembuf consumers_begin[2] = {
    {SF, P, 0},
    {SB, P, 0}};
struct sembuf consumers_end[2] = {
    {SB, V, 0},
    {SE, V, 0}};

// подпрограмма действий производителя
void producer(const int semid, const char *addr)
{
    sleep(rand() % 4 + 1);

    // в начале буфера лежит:
    char **curraddr_prod = (char **)addr;                // указатель на ячейку, в которую запишет производитель
    char **curraddr_cons = (char **)addr + sizeof(char); // указатель на ячейку, c которой будет читать потребитель
    char *alfa = (char *)(curraddr_cons + sizeof(char)); // указатель на букву, которая будет записана следующей

    // захватываем SE и SB семафоры
    int rc = semop(semid, producers_begin, 2);

    if (rc == -1)
    {
        perror("Ошибка semop\n");
        exit(EXIT_FAILURE);
    }

    // помещаем букву в буфер
    **curraddr_prod = *alfa;

    printf("Producer (id = %d) write %c\n", getpid(), **curraddr_prod);

    (*curraddr_prod)++;
    (*alfa)++; // следуюшая буква

    // Проверяем, не выходит ли за пределы алфавита
    if (*alfa > 'z')
        *alfa = 'a'; // Вернуться в начало алфавита

    // освобождаем SB и SE семафоры
    rc = semop(semid, producers_end, 2);

    if (rc == -1)
    {
        perror("Ошибка semop\n");
        exit(EXIT_FAILURE);
    }
}

// подпрограмма действий потребителя
void consumer(const int semid, const char *addr)
{
    sleep(rand() % 10 + 1);

    // в начале буфера лежит:
    char **curraddr_prod = (char **)addr;                // указатель на ячейку, в которую запишет производитель
    char **curraddr_cons = (char **)addr + sizeof(char); // указатель на ячейку, c которой будет читать потребитель
    char *alfa = (char *)(curraddr_cons + sizeof(char)); // указатель на букву, которая будет записана следующей

    // захватываем SF и SB семафоры
    int rc = semop(semid, consumers_begin, 2);

    if (rc == -1)
    {
        perror("Ошибка semop\n");
        exit(EXIT_FAILURE);
    }

    // читаем букву из буфера
    printf("Consumer (id = %d) read %c\n", getpid(), **curraddr_cons);

    (*curraddr_cons)++;

    // освобождаем SB и SF семафоры
    rc = semop(semid, consumers_end, 2);

    if (rc == -1)
    {
        perror("Ошибка semop\n");
        exit(EXIT_FAILURE);
    }
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
    int shmid = shmget(100, BUFFER_SIZE * sizeof(char), IPC_CREAT | perms);

    if (shmid == -1)
    {
        perror("Ошибка shmget.\n");
        exit(EXIT_FAILURE);
    }

    // получаем указатель на начало созданного в функции shmget сегмента
    char *addr = shmat(shmid, 0, 0);

    if (addr == (char *)-1)
    {
        perror("Ошибка shmat.\n");
        exit(EXIT_FAILURE);
    }

    // создаем набор из 3-х семафоров с ключом 100 (c примера)
    // и получаем его идентификатор
    int semid = semget(100, 3, IPC_CREAT | perms);

    if (semid == -1)
    {
        perror("Ошибка semget.\n");
        exit(EXIT_FAILURE);
    }

    // Создание семафоров (3 семафора)
    int rc_sb = semctl(semid, SB, SETVAL, 1);
    int rc_se = semctl(semid, SE, SETVAL, BUFFER_SIZE);
    int rc_sf = semctl(semid, SF, SETVAL, 0);

    if (rc_sb == -1 || rc_se == -1 || rc_sf == -1)
    {
        perror("Ошибка semctl.\n");
        exit(EXIT_FAILURE);
    }

    char **curraddr_prod = (char **)addr;
    char **curraddr_cons = (char **)addr + sizeof(char);
    char *alfa = (char *)(curraddr_cons + sizeof(char));

    *curraddr_cons = alfa + sizeof(char);
    *curraddr_prod = *curraddr_cons;
    *alfa = 'a';

    for (size_t i = 0; i < COUNT_PROD; ++i)
    {
        int child_pid;
        if ((child_pid = fork()) == -1)
        {
            perror("Ошибка fork (producer)");
            exit(EXIT_FAILURE);
        }
        else if (child_pid == 0) // код потомка
        {
            while (flag)
                producer(semid, addr);
            exit(EXIT_SUCCESS);
        }
    }

    for (size_t i = 0; i < COUNT_CONS; ++i)
    {
        int child_pid;
        if ((child_pid = fork()) == -1)
        {
            perror("Ошибка fork (consumer)");
            exit(EXIT_FAILURE);
        }
        else if (child_pid == 0) // код потомка
        {
            while (flag)
                consumer(semid, addr);
            exit(EXIT_SUCCESS);
        }
    }

    for (size_t i = 0; i < COUNT_PROD + COUNT_CONS; ++i)
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

    // удаляем набор семафоров и его структуры данных
    // semnum  игонорируется
    if (semctl(semid, 0, IPC_RMID, NULL) == -1)
    {
        perror("Ошибка удаления набора семафоров.\n");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("Ошибка пометки для удаления\n");
        exit(EXIT_FAILURE);
    }

    // очищаем разделяемую память
    if (shmdt((void *)addr) == -1)
    {
        perror("Ошибка shmdt.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
