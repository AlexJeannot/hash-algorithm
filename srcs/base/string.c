#include "../../incs/base.h"

int32_t process_string(char *input, int32_t args_diff)
{
    t_message   *msg;

    if (args_diff < 2 || !(input))
        args_error("No string provided for -s option", NULL);

    msg = allocate_msg();
    msg->rc_size = strlen(input);
    if (!(msg->raw_content = (char *)malloc(msg->rc_size)))
        fatal_error("string input memory allocation");
    bzero(msg->raw_content, msg->rc_size);
    
    strncpy(msg->raw_content, input, msg->rc_size);
    msg->src_type = SRC_ARG;

    return (1);
}

void    process_stdin(void)
{
    t_message   *msg;
    t_message   *tmp_msg;

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
        fatal_error("stdin source memory allocation");
    bzero(msg->src, msg->rc_size);

    if (msg->rc_size > 0)
        strncpy(msg->src, msg->raw_content, (msg->rc_size - 1));
}