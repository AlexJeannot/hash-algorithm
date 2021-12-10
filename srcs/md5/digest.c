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

char *uint_to_hex(u_int64_t number)
{
    u_int64_t tmp_number;
    int16_t number_char;
    char *output;

    tmp_number = number;

    number_char = 1;
    while (tmp_number /= 16)
        number_char++;
    printf("number_char = %u\n", number_char);
    printf("number = %lu\n", number);
    if (!(output = malloc(number_char)))
        exit(1);

    number_char--;
    for (; number_char >= 0; number_char--) {
        if (number % 16 >= 10)
        {
            //printf("number_char mod 16 - 10 + 'a' = %c\n", number % 16 - 10 + 'a');
            output[number_char] = number % 16 - 10 + 'a';
            // printf("output[%d] = %c\n", number_char, output[number_char]);
        }
        else
        {

            output[number_char] = number % 16 + '0';
            // printf("output[%d] = %c\n", number_char, output[number_char]);
        }
        printf("output[%d] = %c\n", number_char, output[number_char]);
        number /= 16;
    }
    printf("output = %s\n", output);
    return (output);
}

char *build_hash(void *buffers, u_int32_t nb_words)
{
    char        *hash;
    u_int32_t   *buffer;
    u_int8_t    nb_chars;

    nb_chars = (nb_words * 8) + 1;
    if (!(hash = (char *)malloc(nb_chars)))
        exit(1);
    bzero(hash, nb_chars);

    for (u_int32_t count = 0; count < nb_words; count++) {
        buffer = ((u_int32_t *)(buffers)) + count;
        strncat(hash, uint_to_hex(swapuInt32(*buffer)), 8);
    }

    return (hash);
}

char* process_msg(t_message *msg)
{
    t_buffers   buffers;
    t_buffers   save_buffers;
    char        *hash;
    u_int32_t   *(blocks[16]);
    u_int32_t   block_offset;
    u_int32_t   round;

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

    hash = build_hash(&buffers, 4);
    return (hash);
}