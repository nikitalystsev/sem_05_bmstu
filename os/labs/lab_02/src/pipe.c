#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int fd[2]; // Дескрипторы программного канала
    pid_t childpid_arr[2];
    char *messages[2] = {"aaaa",
                         "bbbbbbbbbbbbb"};

    // Создание программного канала
    if (pipe(fd) == -1)
    {
        perror("Ошибка при создании программного канала");
        exit(1);
    }

    for (int i = 0; i < 2; ++i)
    {
        childpid_arr[i] = fork();

        if (childpid_arr[i] == -1)
        {
            perror("Ошибка при создании первого дочернего процесса");
            exit(1);
        }
        else if (childpid_arr[i] == 0)
        {
            // код процесса потомка
            close(fd[0]); // Закрываем чтение из канала
            write(fd[1], messages[i], strlen(messages[i]) + 1);
            exit(0);
        }
    }

    // // Создание первого дочернего процесса (потомка 1)
    // child1 = fork();

    // if (child1 == -1)
    // {
    //     perror("Ошибка при создании первого дочернего процесса");
    //     exit(1);
    // }

    // if (child1 == 0)
    // {
    //     // Код для первого дочернего процесса (потомка 1)
    //     close(fd[0]); // Закрываем чтение из канала
    //     write(fd[1], message1, strlen(message1) + 1);
    //     close(fd[1]); // Закрываем запись в канал
    //     exit(0);
    // }

    // // Создание второго дочернего процесса (потомка 2)
    // child2 = fork();

    // if (child2 == -1)
    // {
    //     perror("Ошибка при создании второго дочернего процесса");
    //     exit(1);
    // }

    // if (child2 == 0)
    // {
    //     // Код для второго дочернего процесса (потомка 2)
    //     close(fd[0]); // Закрываем чтение из канала
    //     write(fd[1], message2, strlen(message2) + 1);
    //     close(fd[1]); // Закрываем запись в канал
    //     exit(0);
    // }

    char buffer[256];
    ssize_t bytes_read;

    for (int i = 0; i < 3; ++i)
    {
        close(fd[1]); // Закрываем запись в канал

        // Считываем сообщения из канала
        bytes_read = read(fd[0], buffer, sizeof(buffer));

        if (bytes_read == 0)
        {
            puts("Больше ничего нет в трубе");
            exit(1);
        }

        if (bytes_read == -1)
        {
            perror("Ошибка при чтении из канала");
            exit(1);
        }

        printf("Родительский процесс получил сообщение: %s\n", buffer);
    }

    // // Код для родительского процесса (предка)
    // close(fd[1]); // Закрываем запись в канал

    // // Считываем сообщения из канала
    // bytes_read = read(fd[0], buffer, sizeof(buffer));

    // if (bytes_read == -1)
    // {
    //     perror("Ошибка при чтении из канала");
    //     exit(1);
    // }

    // printf("Родительский процесс получил сообщение 1: %s\n", buffer);

    // Считываем второе сообщение из канала
    // bytes_read = read(fd[0], buffer, sizeof(buffer));

    // if (bytes_read == -1)
    // {
    //     perror("Ошибка при чтении из канала");
    //     exit(1);
    // }

    // printf("Родительский процесс получил сообщение 2: %s\n", buffer);

    // // Считываем второе сообщение из канала
    // bytes_read = read(fd[0], buffer, sizeof(buffer));

    // if (bytes_read == 0)
    // {
    //     puts("Больше ничего нет в трубе");
    //     exit(1);
    // }

    // close(fd[0]); // Закрываем чтение из канала

    return 0;
}
