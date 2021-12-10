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

int main(int argc, char **argv)
{
    t_message msg;
    char *hash;

    bzero(&msg, sizeof(t_message));

    if (argc <= 1 || argc > 2) {
        printf("Need an argument\n");
        exit(1);
    }

    get_file(&msg, argv[1]);
    get_file_content(&msg);
    format_msg(&msg, TRUE);
    hash = process_msg(&msg);
    printf("hash = %s\n", hash);
    clean_msg(&msg);

    return (0);
}

