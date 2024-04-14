/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "bakery.h"
#include <time.h>
#include <unistd.h> // sleep

void bakery_prog_2(char *host)
{
    CLIENT *clnt;
    struct bakery_t *result_1;
    struct bakery_t get_number_1_arg;
    struct bakery_t *result_2;
    struct bakery_t get_result_1_arg;

#ifndef DEBUG
    clnt = clnt_create(host, BAKERY_PROG, BAKERY_VER, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror(host);
        exit(1);
    }
#endif /* DEBUG */

    time_t start_numb, end_numb, start_wait, end_wait, start_serv, end_serv;

    sleep(rand() % 20 + 1);

    start_numb = clock();

    result_1 = get_number_2(&get_number_1_arg, clnt);

    if (result_1 == (struct bakery_t *)NULL)
    {
        clnt_perror(clnt, "call failed");
    }

    end_numb = clock();

    printf("Клиент (pid = %d) получил номер %d за время %lf \n", getpid(), result_1->number, difftime(end_numb, start_numb));

    sleep(rand() % 40 + 1);

    get_result_1_arg.number = result_1->number;

    start_wait = clock();

    result_2 = get_result_2(&get_result_1_arg, clnt);

    if (result_2 == (struct bakery_t *)NULL)
    {
        clnt_perror(clnt, "call failed");
    }

    end_wait = clock();

    printf("Клиент (pid = %d) получил %c за время %lf \n", getpid(), result_2->result, (difftime(end_numb, start_numb) + difftime(end_wait, start_wait)));

    // time(&raw_time);
    // timeinfo = localtime(&raw_time);
    // gettimeofday(&current_time, NULL);
    // strftime(time_buf, 80, "%H:%M:%S", timeinfo);

    // printf("Клиент (pid = %d) получил ответ %c, time = %s:%ld\n", getpid(), result_2->result, time_buf, current_time.tv_usec);
    // // printf("Клиент (pid = %d) получил ответ %c; время обслуживания = %llu\n", getpid(), result_2->result, resTime);

#ifndef DEBUG
    clnt_destroy(clnt);
#endif /* DEBUG */
}

int main(int argc, char *argv[])
{
    char *host;

    if (argc < 2)
    {
        printf("usage: %s server_host\n", argv[0]);
        exit(1);
    }

    host = argv[1];
    bakery_prog_2(host);
    exit(0);
}
