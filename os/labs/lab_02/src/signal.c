#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int flag = 0;

void sig_handler(int sig_numb)
{
    flag = 1;
    printf("\nОбработчик для сигнала %d установлен.\n", sig_numb);
}

int main()
{
    int fd[2];
    pid_t childpid_arr[2];

    if (pipe(fd) == -1)
    {
        perror("Ошибка pipe");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, sig_handler) == SIG_ERR)
    {
        perror("Ошибка signal");
        exit(EXIT_FAILURE);
    }

    printf("Нажмите Ctrl+C, чтобы разрешить отправку сообщений от дочерних процессов.\n");
    sleep(3);

    for (int i = 0; i < 2; ++i)
        if ((childpid_arr[i] = fork()) == -1)
        {
            perror("Ошибка fork");
            exit(EXIT_FAILURE);
        }
        else if (childpid_arr[i] == 0)
        {
            char *message = (i == 0) ? "aaaa\n" : "bbbbbbbbbbbbb\n";

            if (flag)
            {
                printf("Child (pid: %d) отправил сообщение: %s\n", getpid(), message);
                close(fd[0]); // закрыли на чтение
                write(fd[1], message, strlen(message));
                exit(EXIT_SUCCESS);
            }
            else
            {
                printf("Child (pid: %d) НЕ отправил сообщение\n", getpid());
                exit(EXIT_FAILURE);
            }
        }

    for (size_t i = 0; i < 2; i++)
    {
        pid_t w_pid;
        int status;

        w_pid = wait(&status);

        if (WIFEXITED(status))
        {
            printf("Child process: PID = %d завершился с кодом %d\n",
                   childpid_arr[i], WEXITSTATUS(status));
            if (WEXITSTATUS(status))
                exit(EXIT_FAILURE);
        }
    }

    char elem;

    close(fd[1]); // закрываем на запись

    printf("Полученные сообщения:\n");

    do
    {
        read(fd[0], &elem, 1);
        printf("%s", &elem);
    } while (elem != '\n');

    do
    {
        read(fd[0], &elem, 1);
        printf("%s", &elem);
    } while (elem != '\n');

    return 0;
}
