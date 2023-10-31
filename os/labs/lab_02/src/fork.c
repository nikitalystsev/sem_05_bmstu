#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t childpid_arr[2];

    for (int i = 0; i < 2; ++i)
    {
        if ((childpid_arr[i] = fork()) == -1)
        {
            perror("Can’t fork.\n");
            exit(1);
        }
        else if (childpid_arr[i] == 0)
        {
            // код процесса потомка
            printf("Child process: PID = %d, PPID = %d, GROUP = %d\n",
                   getpid(), getppid(), getpgrp());

            sleep(2); // для получения сирот

            printf("Child process: PID = %d, PPID = %d, GROUP = %d\n",
                   getpid(), getppid(), getpgrp());
            exit(0);
        }
        else
        {
            // код процесса предка
            printf("Parent process: PID = %d, GROUP = %d, childpid_arr[i] = %d\n",
                   getpid(), getpgrp(), childpid_arr[i]);
        }
    }

    return 0;
}
