#include "../../incs/base.h"

void display_help(void)
{
    printf("HELP\n");
}

void display_src(t_message *msg, t_args *args)
{
    if (msg->src_type == SRC_STDIN && args->p)
        printf("(\"%s\") = ", msg->src);
    else if (msg->src_type == SRC_STDIN)
        printf("(stdin) = ");
    else if (msg->src_type == SRC_ARG)
        printf("(\"%s\") = ", msg->raw_content);
    else if (msg->src_type == SRC_FILE)
        printf("(%s) = ", msg->src);
}

void display_hash(t_message *msg, t_args *args)
{
    if (!args->q)
    {
        if (args->algorithm == ALGO_MD5)
            printf("[MD5] ");
        else if (args->algorithm == ALGO_SHA256)
            printf("[SHA256] ");
        
        if (!(args->r))
            display_src(msg, args);
    }
    printf("%s", msg->hash);
    if (!args->q && args->r)
        display_src(msg, args);
    printf("\n");
}