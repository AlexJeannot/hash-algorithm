#include "../../incs/md5.h"

void    fatal_error(const char *reason)
{
    printf("Error: %s\n", reason);
    clean_all_msg();
    exit(1);
}

void    args_error(const char *reason, const char *input)
{
    if (input)
        printf("Error: %s [%s]\n", reason, input);
    else
        printf("Error: %s\n", reason);
    display_help();
    clean_all_msg();
    exit(1);
}