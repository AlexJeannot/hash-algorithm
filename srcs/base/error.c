#include "../../incs/md5.h"

void    fatal_error(char *reason)
{
    ft_putstr_fd("Error: ", 2);
    ft_putstr_fd(reason, 2);
    ft_putstr_fd("\n", 2);
    clean_all_msg();
    exit(1);
}

void    args_error(char *reason, char *input)
{
    ft_putstr_fd("Error: ", 2);
    ft_putstr_fd(reason, 2);
    if (input) {
        ft_putstr_fd("[", 2);
        ft_putstr_fd(input, 2);
        ft_putstr_fd("]", 2);
    }
    ft_putstr_fd("\n", 2);
    display_help();
    clean_all_msg();
    exit(1);
}