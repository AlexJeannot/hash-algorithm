#include "../../incs/md5.h"

round_function r_func[4] = {&f, &g, &h, &i};

void init_buffers(t_buffers *buffers)
{
    bzero(buffers, sizeof(t_buffers));

    buffers->a = 0x67452301;
    buffers->b = 0xefcdab89;
    buffers->c = 0x98badcfe;
    buffers->d = 0x10325476;
}

void store_buffers(t_buffers *buffers, t_buffers *save_buffers)
{
    save_buffers->a = buffers->a;
    save_buffers->b = buffers->b;
    save_buffers->c = buffers->c;
    save_buffers->d = buffers->d;
}

void swap_buffers(t_buffers *buffers)
{
    u_int32_t temp;
    
    temp = buffers->d;
    buffers->d = buffers->c;
    buffers->c = buffers->b;
    buffers->b = buffers->a;
    buffers->a = temp;
}

void add_buffers(t_buffers *buffers, t_buffers *save_buffers)
{
    buffers->a += save_buffers->a;
    buffers->b += save_buffers->b;
    buffers->c += save_buffers->c;
    buffers->d += save_buffers->d;
}

void process_round(t_buffers *buffers, u_int32_t block, u_int32_t round, u_int32_t count)
{
    buffers->a += r_func[round](buffers->b, buffers->c, buffers->d) + block + computed_constants[count];
    buffers->a = (buffers->a << constants[count]) | (buffers->a >> (32 - constants[count]));
    buffers->a += buffers->b;

    swap_buffers(buffers);
}

char *build_hash(t_buffers *buffers, u_int32_t size)
{
    char *hash;

    if (!(hash = (char *)malloc(size)))
        exit(1);
    
    buffers->a = swapuInt32(buffers->a);
    buffers->b = swapuInt32(buffers->b);
    buffers->c = swapuInt32(buffers->c);
    buffers->d = swapuInt32(buffers->d);

    for (int count = 0; count < 4; count++)
    {
        memcpy(&hash[0], &buffers->a, 4);
        memcpy(&hash[4], &buffers->b, 4);
        memcpy(&hash[8], &buffers->c, 4);
        memcpy(&hash[12], &buffers->d, 4);
    }

    printf("%x", swapuInt32(buffers->a));
    printf("%x", swapuInt32(buffers->b));
    printf("%x", swapuInt32(buffers->c));
    printf("%x", swapuInt32(buffers->d));

    return (hash);
}

void process_msg(t_message *msg)
{
    t_buffers buffers;
    t_buffers save_buffers;
    u_int32_t *(blocks[16]);
    u_int32_t block_offset;
    u_int32_t round;

    init_buffers(&buffers);
    while (msg->cc_size < msg->fc_size)
    {
        for (u_int32_t count = 0; count < 16; count++)
        {
            block_offset = msg->cc_size + (count * 4);
            blocks[count] = (u_int32_t *)&msg->fmt_content[block_offset];
        }

        store_buffers(&buffers, &save_buffers);
        round = 0;
        for (u_int32_t count = 0; count < 64; count++)
        {
            if (count % 16 == 0 && count != 0)
                round += 1;
            process_round(&buffers, *blocks[blocks_constants[count]], round, count);
        }
        add_buffers(&buffers, &save_buffers);

        msg->cc_size += 64;
    }

    char *hash = build_hash(&buffers, 16);
    printf("hash = %s\n", hash);

    // printf("\n");
    // printf("%x", swapuInt32(buffers.a));
    // printf("%x", swapuInt32(buffers.b));
    // printf("%x", swapuInt32(buffers.c));
    // printf("%x", swapuInt32(buffers.d));
    // printf("\n");
}