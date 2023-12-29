/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "bakery.h"

void bakery_prog_1(char *host)
{
    CLIENT *clnt;
    struct bakery_t *result_1;
    struct bakery_t get_number_1_arg;
    struct bakery_t *result_2;
    struct bakery_t wait_queue_1_arg;
    struct bakery_t *result_3;
    struct bakery_t bakery_res_1_arg;

#ifndef DEBUG
    clnt = clnt_create(host, BAKERY_PROG, BAKERY_VER, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror(host);
        exit(1);
    }
#endif /* DEBUG */

    srand(time(NULL));
    sleep(rand() % 5 + 1);

    get_number_1_arg.pid = getpid();

    result_1 = get_number_1(&get_number_1_arg, clnt);
    if (result_1 == (struct bakery_t *)NULL)
    {
        clnt_perror(clnt, "call failed");
    }

    printf("Client %d has number %d\n", get_number_1_arg.pid, result_1->number);

    srand(time(NULL));
    sleep(rand() % 7 + 1);

    wait_queue_1_arg.number = result_1->number;
    wait_queue_1_arg.pid = result_1->pid;
    wait_queue_1_arg.idx = result_1->idx;

    result_2 = wait_queue_1(&wait_queue_1_arg, clnt);
    if (result_2 == (struct bakery_t *)NULL)
    {
        clnt_perror(clnt, "call failed");
    }

    sleep(4);

    bakery_res_1_arg.number = wait_queue_1_arg.number;
    bakery_res_1_arg.pid = wait_queue_1_arg.pid;
    bakery_res_1_arg.idx = wait_queue_1_arg.idx;

    result_3 = bakery_res_1(&bakery_res_1_arg, clnt);
    if (result_3 == (struct bakery_t *)NULL)
    {
        clnt_perror(clnt, "call failed");
    }

    printf("Client %d got response %c\n", get_number_1_arg.pid, result_3->result);

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
    bakery_prog_1(host);
    exit(0);
}
