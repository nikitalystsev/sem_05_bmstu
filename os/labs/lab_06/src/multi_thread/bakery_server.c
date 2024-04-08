/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "bakery.h"

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#define _GNU_SOURCE
#include <unistd.h>

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
        if (number[i] > currMax)
            currMax = number[i];

    return currMax;
}

void *bakery(void *arg)
{
    struct bakery_t *targ = arg;

    int i = targ->number - 1;

    for (int j = 0; j < 26; j++)
    {
        while (choosing[j])
            ;
        while ((number[j] > 0) && (number[j] < number[i] || (number[j] == number[i] && j < i)))
            ;
    }

    targ->result = symbol;
    symbol++;

    number[i] = 0;

    return 0;
}

struct bakery_t *
get_number_2_svc(struct bakery_t *argp, struct svc_req *rqstp)
{
    static struct bakery_t result;

    choosing[idx] = true;
    number[idx] = getMaxNumber() + 1;
    choosing[idx] = false;

    result.number = number[idx];

    idx++;

    threadsResults[idxThreadCreate].number = argp->number;

    pthread_create(&workers[idxThreadCreate], NULL, bakery, &threadsResults[idxThreadCreate]);

    idxThreadCreate++;

    return &result;
}

struct bakery_t *
get_result_2_svc(struct bakery_t *argp, struct svc_req *rqstp)
{
    static struct bakery_t result;

    pthread_join(workers[idxThreadJoin], NULL);

    result.number = argp->number;
    result.result = threadsResults[idxThreadJoin].result;

    idxThreadJoin++;

    return &result;
}