#include "../../incs/base.h"

t_message *allocate_msg(void)
{
    t_message *new_msg;
    t_message *tmp_msg;

    tmp_msg = NULL;
    if (!(new_msg = (t_message *)malloc(sizeof(t_message))))
        fatal_error("Malloc"); //todo uniform malloc error message
    bzero(new_msg, sizeof(t_message));

    if (!(list_msg))
        list_msg = new_msg;
    else {
        tmp_msg = list_msg;
        while (tmp_msg->next)
            tmp_msg = tmp_msg->next;
        tmp_msg->next = new_msg; 
    }
    return (new_msg);
}