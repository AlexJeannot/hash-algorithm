#include "../../incs/base.h"

void    display_help(void)
{
    ft_putstr_fd("\nUsage: algorithm [-p -q -r] [-s string] [file...]\n", 2);
    ft_putstr_fd("    algorithm       Algorithm to hash input (md5/sha256)\n", 2);
    ft_putstr_fd("    file            files to digest\n", 2);
    ft_putstr_fd("    -p              Process STDIN input\n", 2);
    ft_putstr_fd("    -q              Quiet mode (output hash only)\n", 2);
    ft_putstr_fd("    -r              Reverse mode (output source after the hash)\n", 2);
    ft_putstr_fd("    -s              Process string\n", 2);
    ft_putstr_fd("\nexamples:\n", 2);
    ft_putstr_fd("    ./ft_ssl file.txt\n", 2);
    ft_putstr_fd("    ./ft_ssl -s \"hello world\"\n", 2);
    ft_putstr_fd("    echo \"hello world\" | ./ft_ssl\n", 2);
    ft_putstr_fd("    echo \"hello world\" | ./ft_ssl -p file.txt\n", 2);
    ft_putstr_fd("    echo \"hello world\" | ./ft_ssl -p -s \"hello world\" file.txt\n", 2);
}

void    display_src(t_message *msg, t_args *args)
{
    if (args->r)
        ft_putstr_fd(" ", 1);
    if (msg->src_type == SRC_STDIN && args->p) {
        ft_putstr_fd("(\"", 1);
        ft_putstr_fd(msg->src, 1);
        ft_putstr_fd("\")", 1);
    }
    else if (msg->src_type == SRC_STDIN)
        ft_putstr_fd("(stdin)", 1);
    else if (msg->src_type == SRC_ARG) {
        ft_putstr_fd("(\"", 1);
        ft_putstr_fd(msg->raw_content, 1);
        ft_putstr_fd("\")", 1);
    }
    else if (msg->src_type == SRC_FILE) {
        ft_putstr_fd("(", 1);
        ft_putstr_fd(msg->src, 1);
        ft_putstr_fd(")", 1);
    }
    if (!args->r)
        ft_putstr_fd(" = ", 1);
}

void    display_hash(t_message *msg, t_args *args)
{
    if (msg->nofile) {
        ft_putstr_fd("Error: no such file [", 2);
        ft_putstr_fd(msg->src, 2);
        ft_putstr_fd("]\n", 2);
        return ;
    }
    if (!args->q)
    {
        if (args->algorithm == ALGO_MD5)
            ft_putstr_fd("[MD5] ", 1);
        else if (args->algorithm == ALGO_SHA256)
            ft_putstr_fd("[SHA256] ", 1);
        
        if (!(args->r))
            display_src(msg, args);
    }
    ft_putstr_fd(msg->hash, 1);
    if (!args->q && args->r)
        display_src(msg, args);
    ft_putstr_fd("\n", 1);
}