#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t childpid_arr[2];

    int status;

    for (int i = 0; i < 2; ++i)
    {
        childpid_arr[i] = fork();

        if (childpid_arr[i] == -1)
        {
            perror("Can’t fork.\n");
            exit(1);
        }
        else if (childpid_arr[i] == 0)
        {
            // код процесса потомка
            printf("Child process: PID = %d, PPID = %d, GROUP = %d\n",
                   getpid(), getppid(), getpgrp());
            exit(0);
        }
        else
        {
            // код процесса предка
            printf("Parent process: PID = %d, GROUP = %d, childpid[i] = %d\n",
                   getpid(), getpgrp(), childpid_arr[i]);
        }
    }

    for (size_t i = 0; i < 2; i++)
    {
        pid_t child_pid;
        int status;

        child_pid = waitpid(childpid_arr[i], &status, WNOHANG);

        if (WIFEXITED(status))
        {
            printf("Child process: PID = %d exited with code %d\n",
                   childpid_arr[i], WEXITSTATUS(status));
        }
    }

    return 0;
}
