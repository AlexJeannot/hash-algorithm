#include "../../incs/base.h"

u_int8_t is_option(char *input)
{
    if (input && input[0] == '-')
        return (TRUE);
    return (FALSE);
}

void get_algorithm(t_args *args, char *input)
{
    if (strncmp(input, "md5", 3) == 0)
        args->algorithm = ALGO_MD5;
    else if (strncmp(input, "sha256", 6) == 0)
        args->algorithm = ALGO_SHA256;
    else
        args_error("Wrong algorithm provided", input);
}

int32_t process_string(char *input, int32_t args_diff)
{
    t_message *msg;

    if (args_diff < 2 || !(input))
        args_error("No string provided for -s option", NULL);

    msg = allocate_msg();
    msg->rc_size = strlen(input);
    if (!(msg->raw_content = (char *)malloc(msg->rc_size)))
        fatal_error("malloc");
    strncpy(msg->raw_content, input, msg->rc_size);
    msg->src_type = SRC_ARG;

    return (1);
}

int32_t parse_options(t_args *args, char *input, char *next_input, int32_t args_diff)
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

void process_stdin(void)
{
    t_message *msg;
    t_message *tmp_msg;

    msg = get_file_content(STDIN_FILENO);
    tmp_msg = list_msg;
    if (tmp_msg != msg)
    {
        while (tmp_msg->next != msg)
            tmp_msg = tmp_msg->next;
        tmp_msg->next = NULL;
        msg->next = list_msg;
        list_msg = msg;
    }
    msg->src_type = SRC_STDIN;
    if (!(msg->src = (char *)malloc(msg->rc_size)))
        fatal_error("malloc");
    bzero(msg->src, msg->rc_size);
    if (msg->rc_size > 0)
        strncpy(msg->src, msg->raw_content, (msg->rc_size - 1));
}

void parse_args(int nb_args, char **list_args, t_args *args)
{
    int32_t index_args;

    if (nb_args < 1) {
        args_error("No hash algorithm provided", NULL);
        exit(1);
    }

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