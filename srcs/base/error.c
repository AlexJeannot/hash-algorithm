#include "../../incs/md5.h"

void fatal_error(char *reason)
{
    printf("Error: %s\n", reason);
    exit(1);
}