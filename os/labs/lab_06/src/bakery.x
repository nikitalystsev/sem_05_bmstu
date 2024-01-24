struct bakery_t
{
    int number;
    int result;
};

program BAKERY_PROG
{
    version BAKERY_VER
    {
        struct bakery_t get_number(struct bakery_t) = 1; 
        struct bakery_t get_result(struct bakery_t) = 2;
    } = 2; 
} = 0x20000001;
