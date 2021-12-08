#include "../../incs/md5.h"

void clean_msg(t_message *msg)
{
    if (msg->raw_content)
        free(msg->raw_content);

    if (msg->fmt_content)
        free(msg->fmt_content);
}