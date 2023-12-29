/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "bakery.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

time_t raw_time;
struct tm *timeinfo;

int choosing[26] = {0};
int number[26] = {0};
int symbol = 'a';
int idx = 0;

struct bakery_t threadsResults[26] = {0};
pthread_t workers[26];
int idxThreadCreate = 0;
int idxThreadJoin = 0;

int getMaxNumber()
{
    int currMax = number[0];

    for (int i = 1; i < 26; i++)
        if (numbers[i] > currMax)
            currMax = numbers[i];

    return currMax;
}

void *bakery(void *arg)
{
    setbuf(stdout, NULL);
    time(&raw_time);
    timeinfo = localtime(&raw_time);
    struct bakery_t *targ = arg;
    printf("Thread id = '%ld' started, client's number = %d, time = %s", gettid(), number[targ->idx], asctime(timeinfo));

    int i = targ->id;
    for (int j = 0; j < 26; j++)
    {
        while (choosing[j])
            ;
        while ((number[j] > 0) && (number[j] < number[i] || (number[j] == number[i] && j < i)))
            ;
    }

    targ->res = symbol;
    symbol++;

    sleep(5);
    time(&raw_time);
    timeinfo = localtime(&raw_time);
    printf("Thread id = '%ld' stopped, client's number = %d, time = %s", gettid(), number[i], asctime(timeinfo));
    number[i] = 0;

    return 0;
}

struct bakery_t *
get_number_1_svc(struct bakery_t *argp, struct svc_req *rqstp)
{
    static struct bakery_t result;

    printf("Client (pid: %d) logged to server\n", argp->pid);

    choosing[idx] = true;
    numbers[idx] = getMaxNumber() + 1;
    choosing[idx] = false;

    result.number = numbers[idx];
    result.pid = argp->pid;
    result.idx = idx;

    idx++;

    return &result;
}

struct bakery_t *
wait_queue_1_svc(struct bakery_t *argp, struct svc_req *rqstp)
{
    static struct bakery_t result;

    threads_results[idxThreadCreate].id = argp->pid;
    pthread_create(&workers[idxThreadCreate], NULL, bakery, &threads_results[idxThreadCreate]);
    idxThreadCreate++;

    return &result;
}

struct bakery_t *
bakery_res_1_svc(struct bakery_t *argp, struct svc_req *rqstp)
{
    static struct bakery_t result;

    pthread_join(workers[idxThreadJoin], NULL);

    result.number = argp->number;
    result.pid = argp->pid;
    result.idx = argp->idx;

    result.result = threads_results[idxThreadJoin].res;

    idxThreadJoin++;

    return &result;
}
