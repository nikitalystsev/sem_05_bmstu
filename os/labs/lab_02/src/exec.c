#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t childpid_arr[2];

    char *progs[2] = {"./sum_num.exe", "./scalar_prod.exe"};

    for (int i = 0; i < 2; ++i)
        if ((childpid_arr[i] = fork()) == -1)
        {
            perror("Ошибка fork");
            exit(EXIT_FAILURE);
        }
        else if (childpid_arr[i] == 0)
        {
            // код процесса потомка
            printf("Child process: PID = %d, PPID = %d, GROUP = %d\n",
                   getpid(), getppid(), getpgrp());

            if (execv(progs[i], NULL) == -1)
            {
                perror("Ошибка exec\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // код процесса предка
            printf("Parent process: PID = %d, GROUP = %d, childpid_arr[i] = %d\n",
                   getpid(), getpgrp(), childpid_arr[i]);
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

    return 0;
}
