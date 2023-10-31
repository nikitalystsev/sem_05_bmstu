#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int fd[2];
    pid_t childpid_arr[2];
    char *messages[2] = {"aaaa\n", "bbbbbbbbbbbbb\n"};

    if (pipe(fd) == -1)
    {
        perror("Ошибка pipe");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 2; ++i)
        if ((childpid_arr[i] = fork()) == -1)
        {
            perror("Ошибка fork");
            exit(EXIT_FAILURE);
        }
        else if (childpid_arr[i] == 0)
        {
            close(fd[0]); // Закрываем чтение из канала
            write(fd[1], messages[i], strlen(messages[i]));
            exit(EXIT_SUCCESS);
        }

    for (size_t i = 0; i < 2; i++)
    {
        pid_t w_pid;
        int status;

        w_pid = wait(&status);

        if (WIFEXITED(status))
        {
            printf("Child process: PID = %d завершился с кодом %d\n",
                   w_pid, WEXITSTATUS(status));
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

    char buffer[256];

    for (int i = 0; i < 2; ++i)
    {
        close(fd[1]); // Закрываем запись в канал
        read(fd[0], buffer, strlen(messages[i]));
        printf("Родительский процесс получил сообщение: %s\n", buffer);
        buffer[0] = '\0';
    }

    close(fd[1]); // Закрываем запись в канал
    read(fd[0], buffer, sizeof(char));
    printf("buffer после получения сообщений от потомков:%s\n", buffer);

    return 0;
}
