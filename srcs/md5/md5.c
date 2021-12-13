#include "../../incs/md5.h"

void md5(t_message *msg)
{
    // printf("msg->raw_content 2 = %s\n", msg->raw_content);
    format_msg(msg, FALSE);
    // printf("msg->raw_content 3 = %s\n", msg->raw_content);
    process_msg_md5(msg);
}