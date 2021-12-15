#include "../../incs/sha256.h"

u_int32_t rotate_left(u_int32_t x, u_int32_t offset)
{
    return ((x << offset) | (x >> (32 - offset)));
}

u_int32_t rotate_right(u_int32_t x, u_int32_t offset)
{
    return ((x >> offset) | (x << (32 - offset)));
}

u_int32_t shift_right(u_int32_t x, u_int32_t offset)
{
    return (x >> offset);
}

void sha256(t_message *msg)
{
    format_msg(msg, TRUE);
    process_msg_sha256(msg);
}

