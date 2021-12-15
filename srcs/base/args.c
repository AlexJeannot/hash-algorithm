#include "../../incs/base.h"

u_int8_t    is_option(char *input)
{
    if (input && input[0] == '-')
        return (TRUE);
    return (FALSE);
}

int32_t     parse_options(t_args *args, char *input, char *next_input, int32_t args_diff)
{
    if (!input)
        args_error("No option provided", NULL);
    else if (strlen(input) != 2)
        args_error("Wrong option provided", input);
    else if (input[1] == 'p') {
        if (args->p == TRUE)
            args_error("Option provided twice", input);
        args->p = TRUE;
    }
    else if (input[1] == 'q') {
        if (args->q == TRUE)
            args_error("Option provided twice", input);
        args->q = TRUE;
    }
    else if (input[1] == 'r') {
        if (args->r == TRUE)
            args_error("Option provided twice", input);
        args->r = TRUE;
    }
    else if (input[1] == 's')
        return (process_string(next_input, args_diff));
    else
        args_error("Wrong option provided", input);
    return (0);
}

void        get_algorithm(t_args *args, char *input)
{
    if (strncmp(input, "md5", 3) == 0)
        args->algorithm = ALGO_MD5;
    else if (strncmp(input, "sha256", 6) == 0)
        args->algorithm = ALGO_SHA256;
    else
        args_error("Wrong algorithm provided", input);
}

void        parse_args(int nb_args, char **list_args, t_args *args)
{
    int32_t index_args;

    if (nb_args < 1)
        args_error("No hash algorithm provided", NULL);

    index_args = 0;
    get_algorithm(args, list_args[index_args++]);

    for (; index_args < nb_args; index_args++)
    {
        if (is_option(list_args[index_args]))
            index_args += parse_options(args, list_args[index_args], list_args[index_args + 1], (nb_args - index_args));
        else 
            break;
    }
    for (; index_args < nb_args; index_args++)
        process_file(list_args[index_args]);
    
    if (args->p == TRUE || list_msg == NULL)
        process_stdin();
}