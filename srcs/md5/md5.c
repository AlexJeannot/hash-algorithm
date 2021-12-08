#include "../../incs/md5.h"

round_function r_func[4] = {&f, &g, &h, &i};

void init_buffers(t_buffers *buffers)
{
    buffers->a = 0x67452301;
    buffers->b = 0xefcdab89;
    buffers->c = 0x98badcfe;
    buffers->d = 0x10325476;
}

u_int32_t f(u_int32_t x, u_int32_t y, u_int32_t z)
{
    return ((x & y) | ((~x) & z));
}

u_int32_t g(u_int32_t x, u_int32_t y, u_int32_t z)
{
    return ((x & z) | (y & (~z)));
}

u_int32_t h(u_int32_t x, u_int32_t y, u_int32_t z)
{
    return (x ^ y ^ z);
}

u_int32_t i(u_int32_t x, u_int32_t y, u_int32_t z)
{
    return (y ^ (x | (~z)));
}

u_int32_t process_round(u_int32_t a, u_int32_t b, u_int32_t c, u_int32_t d, u_int32_t block, u_int32_t round, u_int32_t count)
{
    a += r_func[round](b, c, d) + block + computed_constants[count];
    a = (a << constants[count]) | (a >> (32 - constants[count]));
    a += b;

    return (a);
}

void process_msg(t_message *msg, t_buffers *buffers)
{
    u_int32_t *(current_blocks[16]);
    (void)buffers;

    u_int32_t a;
    u_int32_t b;
    u_int32_t c;
    u_int32_t d;

    while (msg->cc_size < msg->fc_size) {
        for (u_int32_t count = 0; count < 16; count++) {
            current_blocks[count] = (u_int32_t *)&msg->fmt_content[msg->cc_size + count * 4];
            printf("current_blocks = %u\n", *(current_blocks[count]));
        }

        a = buffers->a;
        b = buffers->b;
        c = buffers->c;
        d = buffers->d;

        u_int32_t round = 0;
        for (u_int32_t count = 0; count < 64;)
        {
            if (count % 16 && count != 0)
                round += 1;
            
            printf("BEFORE process\n");
            a = process_round(a, b, c, d, *current_blocks[blocks_constants[count]], round, count); /* 1 */
            count++;
            d = process_round(d, a, b, c, *current_blocks[blocks_constants[count]], round, count); /* 2 */
            count++;
            c = process_round(c, d, a, b, *current_blocks[blocks_constants[count]], round, count); /* 3 */
            count++;
            b = process_round(b, c, d, a, *current_blocks[blocks_constants[count]], round, count); /* 4 */
            count++;
            a = process_round(a, b, c, d, *current_blocks[blocks_constants[count]], round, count); /* 5 */
            count++;
            d = process_round(d, a, b, c, *current_blocks[blocks_constants[count]], round, count); /* 6 */
            count++;
            c = process_round(c, d, a, b, *current_blocks[blocks_constants[count]], round, count); /* 7 */
            count++;
            b = process_round(b, c, d, a, *current_blocks[blocks_constants[count]], round, count); /* 8 */
            count++;
            a = process_round(a, b, c, d, *current_blocks[blocks_constants[count]], round, count); /* 9 */
            count++;
            d = process_round(d, a, b, c, *current_blocks[blocks_constants[count]], round, count); /* 10 */
            count++;
            c = process_round(c, d, a, b, *current_blocks[blocks_constants[count]], round, count); /* 11 */
            count++;
            b = process_round(b, c, d, a, *current_blocks[blocks_constants[count]], round, count); /* 12 */
            count++;
            a = process_round(a, b, c, d, *current_blocks[blocks_constants[count]], round, count); /* 13 */
            count++;
            d = process_round(d, a, b, c, *current_blocks[blocks_constants[count]], round, count); /* 14 */
            count++;
            c = process_round(c, d, a, b, *current_blocks[blocks_constants[count]], round, count); /* 15 */
            count++;
            b = process_round(b, c, d, a, *current_blocks[blocks_constants[count]], round, count); /* 16 */
            count++;
        }
        

        buffers->a += a;
        buffers->b += b;
        buffers->c += c;
        buffers->d += d;

        msg->cc_size += 64;
    }

    printf("\n");
    printf("%x", buffers->a);
    printf("%x", buffers->b);
    printf("%x", buffers->c);
    printf("%x", buffers->d);
    printf("\n");


}

int main(int argc, char **argv) 
{
    t_message msg;
    t_buffers buffers;

    bzero(&msg, sizeof(t_message));
    bzero(&buffers, sizeof(t_buffers));

    if (argc <= 1 || argc > 2) {
        printf("Need an argument\n");
        exit(1);
    }

    get_file(&msg, argv[1]);
    get_file_content(&msg);
    printf("RAW CONTENT = %s\n", msg.raw_content);

    format_msg(&msg);
    printf("FMT CONTENT = %s\n", msg.fmt_content);

    init_buffers(&buffers);

    process_msg(&msg, &buffers);


    // for (u_int32_t count = 0; count < 64, count++)
    // {
    //     if (count % 16 && count != 0)
    //         round += 1
        
    //     a = process_round(a, b, c, d, block[block_constants[count]], round, count); /* 1 */
    //     d = process_round(d, a, b, c, block[block_constants[count]], round, count); /* 2 */
    //     c = process_round(c, d, a, b, block[block_constants[count]], round, count); /* 3 */
    //     b = process_round(b, c, d, a, block[block_constants[count]], round, count); /* 4 */
    //     a = process_round(a, b, c, d, block[block_constants[count]], round, count); /* 5 */
    //     d = process_round(d, a, b, c, block[block_constants[count]], round, count); /* 6 */
    //     c = process_round(c, d, a, b, block[block_constants[count]], round, count); /* 7 */
    //     b = process_round(b, c, d, a, block[block_constants[count]], round, count); /* 8 */
    //     a = process_round(a, b, c, d, block[block_constants[count]], round, count); /* 9 */
    //     d = process_round(d, a, b, c, block[block_constants[count]], round, count); /* 10 */
    //     c = process_round(c, d, a, b, block[block_constants[count]], round, count); /* 11 */
    //     b = process_round(b, c, d, a, block[block_constants[count]], round, count); /* 12 */
    //     a = process_round(a, b, c, d, block[block_constants[count]], round, count); /* 13 */
    //     d = process_round(d, a, b, c, block[block_constants[count]], round, count); /* 14 */
    //     c = process_round(c, d, a, b, block[block_constants[count]], round, count); /* 15 */
    //     b = process_round(b, c, d, a, block[block_constants[count]], round, count); /* 16 */
    // }


    clean_msg(&msg);
    return (0);
}