/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "bakery.h"
#include <time.h>
#include <unistd.h> // sleep

unsigned long long getMicrosecondsCpuTime()
{
    struct timespec t;

    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t))
    {
        perror("clock_gettime");
        return 0;
    }

    return t.tv_sec * 1000000LL + t.tv_nsec / 1000; // Возвращаем время в микросекундах
}

void bakery_prog_2(char *host)
{
    CLIENT *clnt;
    struct bakery_t *result_1;
    struct bakery_t get_number_2_arg;
    struct bakery_t *result_2;
    struct bakery_t bakery_service_2_arg;

#ifndef DEBUG
    clnt = clnt_create(host, BAKERY_PROG, BAKERY_VER, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror(host);
        exit(1);
    }
#endif /* DEBUG */

    struct timeval current_time;

    time_t raw_time;
    struct tm *timeinfo;
    char time_buf[80];

    srand(time(NULL));
    int interval = rand() % 5 + 1;
    sleep(interval);

    result_1 = get_number_2(&get_number_2_arg, clnt);
    if (result_1 == (struct bakery_t *)NULL)
    {
        clnt_perror(clnt, "call failed");
    }

    srand(time(NULL));
    interval = rand() % 5 + 1;
    sleep(interval);

    unsigned long long time, resTime = 0;

    time = getMicrosecondsCpuTime();
    result_2 = bakery_service_2(&bakery_service_2_arg, clnt);
    resTime = getMicrosecondsCpuTime() - time;

    if (result_2 == (struct bakery_t *)NULL)
    {
        clnt_perror(clnt, "call failed");
    }

    // time(&raw_time);
    // timeinfo = localtime(&raw_time);
    // gettimeofday(&current_time, NULL);
    // strftime(time_buf, 80, "%H:%M:%S", timeinfo);

    // printf("Клиент (pid = %d) получил ответ %c, time = %s:%ld\n", getpid(), result_2->result, time_buf, current_time.tv_usec);
    printf("Клиент (pid = %d) получил ответ %c; время обслуживания = %llu\n", getpid(), result_2->result, resTime);

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
