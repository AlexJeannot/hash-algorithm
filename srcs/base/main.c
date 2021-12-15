#include "../../incs/base.h"

t_message *list_msg;

int main(int argc, char **argv)
{
    t_args args;
    t_message *msg;

    list_msg = NULL;
    bzero(&args, sizeof(t_args));
    parse_args((argc - 1), &argv[1], &args);
    msg = list_msg;
    while (msg)
    {
        if (!msg->nofile)
        {
            if (args.algorithm == ALGO_MD5)
                md5(msg);
            else if (args.algorithm == ALGO_SHA256)
                sha256(msg);
        }
        display_hash(msg, &args);
        clean_msg(msg);
        msg = msg->next;
    }
}