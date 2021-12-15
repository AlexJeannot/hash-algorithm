#include "../../incs/md5.h"

void md5(t_message *msg)
{
    format_msg(msg, FALSE);
    process_msg_md5(msg);
}