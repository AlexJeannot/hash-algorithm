#include "../../incs/base.h"

void parse_args(int nb_args, char **args, t_message *msg)
{
    for (int32_t count = 0; count < nb_args; count++)
    {
        printf("args nb %u: %s\n", count, args[count]);
    }
    if (nb_args <= 0 || nb_args > 1) {
        printf("Need an argument\n");
        exit(1);
    }

    get_file(msg, args[0]);
    get_file_content(msg);
}

int main(int argc, char **argv)
{
    t_message msg;
    char *hash;

    bzero(&msg, sizeof(t_message));
    parse_args((argc - 1), &argv[1], &msg);
    hash = md5(&msg);
    printf("HASH = %s\n", hash);
}