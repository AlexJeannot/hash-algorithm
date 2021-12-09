#include "../../incs/md5.h"

void format_msg(t_message *msg)
{

    msg->fc_size = msg->rc_size + 8 + (64 - ((msg->rc_size + 8) % 64));

    if (!(msg->fmt_content = (char *)malloc(msg->fc_size * sizeof(char)))) {
        clean_msg(msg);
        fatal_error("Format message malloc");
    }

    memcpy(msg->fmt_content, msg->raw_content, msg->rc_size);
    msg->fmt_content[msg->rc_size] = 0b10000000;
    *(u_int64_t *)&(msg->fmt_content[msg->fc_size - 8]) = msg->rc_size * 8;
    //*(u_int64_t *)&(msg->fmt_content[msg->fc_size - 8]) = swapuInt64(msg->rc_size * 8);
    //msg->fmt_content[0] = swapuInt64(msg->rc_size);
}