#include "../../incs/md5.h"

void fatal_error(char *reason)
{
    printf("Error: %s\n", reason);
    exit(1);
}

void args_error(char *reason, char *input)
{
    if (input)
        printf("Error: %s [%s]\n", reason, input);
    else
        printf("Error: %s\n", reason);
    display_help();
    exit(1);
}
