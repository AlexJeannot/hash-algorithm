#include "../../incs/base.h"

char *uint_to_hex(u_int64_t number)
{
    u_int64_t tmp_number;
    int16_t nb_char;
    int16_t nb_zero;
    char *output;

    tmp_number = number;
    nb_char = 1;
    while (tmp_number /= 16)
        nb_char++;
    if (!(output = malloc(8)))
        fatal_error("hash block memory allocation");
    bzero(output, 8);

    nb_char -= 1;
    nb_zero = 0;
    while (nb_char < 7) {
        nb_zero++;
        nb_char++;
    }

    for (; (nb_char - nb_zero) >= 0; nb_char--) {
        if (number % 16 >= 10)
            output[nb_char] = number % 16 - 10 + 'a';
        else
            output[nb_char] = number % 16 + '0';
        number /= 16;
    }

    nb_zero -= 1;
    for (; nb_zero >= 0; nb_zero--)
        output[nb_zero] = '0';
    return (output);
}

void build_hash(t_message *msg, void *buffers, u_int32_t nb_words, u_int8_t swap)
{
    char        *hash;
    char        *hash_block;
    u_int32_t   *buffer;
    u_int8_t    nb_chars;

    nb_chars = (nb_words * 8) + 1;
    if (!(hash = (char *)malloc(nb_chars)))
        fatal_error("hash memory allocation");
    bzero(hash, nb_chars);

    for (u_int32_t count = 0; count < nb_words; count++) {
        buffer = ((u_int32_t *)(buffers)) + count;
        if (swap == TRUE)
            hash_block = uint_to_hex(swap_uint_32(*buffer));
        else
            hash_block = uint_to_hex(*buffer);
        strncat(hash, hash_block, 8);
        free(hash_block);
    }
    msg->hash = hash;
}