struct bakery_t
{
    int number;
    int idx;
    int pid;
    int result;
};

program BAKERY_PROG
{
    version BAKERY_VER
    {
        struct bakery_t get_number(struct bakery_t) = 1; 
        struct bakery_t wait_queue(struct bakery_t) = 2;
        struct bakery_t bakery_res(struct bakery_t) = 3;
    } = 1; 
} = 0x20000001;
